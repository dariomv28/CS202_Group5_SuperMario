#include "Headers/PhysicsEngine.h"
#include "Headers/GameEventMediator.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/LivingEntity.h"
#include "Headers/Enemy.h"
#include "Headers/PowerUpObject.h"

PhysicsEngine::PhysicsEngine() {
	gravity = sf::Vector2f(0, 2500.f);
	friction = sf::Vector2f(1000.f, 0);
}

void PhysicsEngine::setEventMediator(GameEventMediator* mediator) {
	this->eventMediator = mediator;
}

void PhysicsEngine::applyGravity(LivingEntity* entity, const float& dt) {
	sf::Vector2f currentVelocity = entity->getVelocity();

	currentVelocity.y += gravity.y * dt;

	if (currentVelocity.y > entity->movementComponent->MAX_FALL_SPEED) {
		currentVelocity.y = entity->movementComponent->MAX_FALL_SPEED;
	}

	entity->setVelocity(currentVelocity);
}

void PhysicsEngine::applyFriction(LivingEntity* entity, const float& dt) {
	if (entity->getVelocity().x > 0) {
		entity->setVelocity(entity->getVelocity() - friction * dt);
		if (entity->getVelocity().x < 0) {
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
		}
	}
	else if (entity->getVelocity().x < 0) {
		entity->setVelocity(entity->getVelocity() + friction * dt);
		if (entity->getVelocity().x > 0) {
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
		}
	}
}

Side PhysicsEngine::CollisionType(GameObject* obj1, GameObject* obj2)
{
	sf::FloatRect boxX = obj1->hitbox.getGlobalBounds();
	sf::FloatRect boxY = obj2->hitbox.getGlobalBounds();

	sf::Vector2f centerX = boxX.getPosition() + boxX.getSize() / 2.f;
	sf::Vector2f centerY = boxY.getPosition() + boxY.getSize() / 2.f;

	float dx = centerY.x - centerX.x;
	float dy = centerY.y - centerX.y;

	float overlapX = boxX.width / 2.f + boxY.width / 2.f - std::abs(dx);
	float overlapY = boxX.height / 2.f + boxY.height / 2.f - std::abs(dy);

	if (overlapX >= 0 && overlapY >= 0) {
		if (overlapX >= overlapY) {
			return (dy > 0) ? Side::Collide_Bottom : Side::Collide_Top;
		}
		else return (dx < 0) ? Side::Collide_Left : Side::Collide_Right;
	}
	else return Side::Collide_None;
}

void PhysicsEngine::fixPosition(LivingEntity* entity, GameObject* obj, Side collidedSide) {
	//std::cerr << "velocity: " << entity->getVelocity().x << " " << entity->getVelocity().y << "\n";
	switch (collidedSide) {
	case Collide_Top:	
		entity->setPosition(sf::Vector2f(entity->hitbox.getPosition().x, obj->hitbox.getPosition().y + obj->hitbox.getSize().y));
		break;
	case Collide_Bottom:
		entity->setPosition(sf::Vector2f(entity->hitbox.getPosition().x, obj->hitbox.getPosition().y - entity->hitbox.getSize().y));
		break;
	case Collide_Left:
		entity->setPosition(sf::Vector2f(obj->hitbox.getPosition().x + obj->hitbox.getSize().x,entity->hitbox.getPosition().y));
		break;
	case Collide_Right:
		entity->setPosition(sf::Vector2f(obj->hitbox.getPosition().x - entity->hitbox.getSize().x, entity->hitbox.getPosition().y));
		break;
	}
}

//void PhysicsEngine::resolveCollisionPlayerBlock(PlayerManager* entity, std::vector<Block*>& blocks, const float& dt) {
//	// Resolve on the ground
//	entity->setOnGround(false);
//	/*0 is Bottom
//	1 is Top
//	2 is Left
//	3 is Right*/
//	//Make reaction of the blocks first
//	for (auto& obj : blocks) {
//		if (obj->getExist() == false) continue;
//		Side Type = CollisionType(entity, obj);
//		if (Type != Collide_None) {
//			obj->reactToCollison(Type ^ 1);
//		}
//	}
//	for (auto& obj : blocks)
//	{
//		if (obj->getExist() == false) continue;
//
//		//Resolve the right side
//		Side Type = CollisionType(entity, obj);
//		if (Type != Collide_None) fixPosition(entity, obj, Type);
//		switch (Type) {
//		case (Collide_Bottom):
//			//fixPosition(entity, obj, Collide_Bottom);
//			entity->setOnGround(true);
//			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
//			entity->movementComponent->resetJumps();
//			//std::cerr << "Collide Bottom\n";
//			continue;
//		case (Collide_Top):
//			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
//			//std::cerr << "Collide Top\n";
//			continue;
//
//		case (Collide_Right):
//			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
//			entity->setMoveRight(false);
//			//std::cerr << "Collide Right\n";
//			continue;
//		case (Collide_Left):
// 			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
//			entity->setMoveLeft(false);
//			//std::cerr << "Collide Left\n";
//			continue;
//		}
//	}
//
//	//std::cerr << entity->getVelocity().x << std::endl;
//	//fixPosition(entity, Blocks_Collide);
//	
//
//}

void PhysicsEngine::resolveCollisionPlayerBlock(PlayerManager* entity, std::vector<Block*>& blocks, const float& dt) {
	entity->setOnGround(false);
	entity->setMoveLeft(true);  // Reset movement restrictions at start of frame
	entity->setMoveRight(true);

	bool hasBottomCollision = false;
	bool hasLeftCollision = false;
	bool hasRightCollision = false;
	bool hasTopCollision = false;

	// Store original position in case we need to revert
	sf::Vector2f originalPosition = entity->getPosition();

	// First pass: Check all collisions and record them
	for (auto& obj : blocks) {
		if (!obj->getExist()) continue;

		Side Type = CollisionType(entity, obj);
		if (Type != Collide_None) {
			obj->reactToCollison(Type ^ 1);

			// Record collision types
			switch (Type) {
			case Collide_Bottom:
				hasBottomCollision = true;
				break;
			case Collide_Left:
				hasLeftCollision = true;
				break;
			case Collide_Right:
				hasRightCollision = true;
				break;
			case Collide_Top:
				hasTopCollision = true;
				break;
			}

			fixPosition(entity, obj, Type);
		}
	}

	if (hasBottomCollision) {
		entity->setOnGround(true);
		entity->setVelocity(sf::Vector2f(entity->getVelocity().x, -10.0f));
		entity->movementComponent->resetJumps();
	}

	if (hasTopCollision) {
		entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
	}

	if (hasLeftCollision) {
		entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
		entity->setMoveLeft(false);
	}

	if (hasRightCollision) {
		entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
		entity->setMoveRight(false);
	}

}

void PhysicsEngine::resolveCollisionPlayerEnemy(PlayerManager* entity, std::vector<Enemy*>& enemies, const float& dt) {
	for (auto& obj : enemies) {
		//Resolve the right side
		Side Type = CollisionType(entity, obj);
		if (Type != Collide_None) fixPosition(entity, obj, Type);
		switch (Type) {
		case Collide_Right:
			obj->reactToPlayerCollision(Collide_Left);
			continue;

		case Collide_Left:
			obj->reactToPlayerCollision(Collide_Right);
			continue;

		case Collide_Bottom:
			entity->movementComponent->resetJumps();
			obj->reactToPlayerCollision(Collide_Top);
			continue;

		case Collide_Top:
			obj->reactToPlayerCollision(Collide_Bottom);
			continue;
		}
	}
}

void PhysicsEngine::resolveCollisionPlayerEnemy2(PlayerManager* entity, std::vector<Enemy*>& enemies, std::vector<Block*>& blocks, const float& dt) {
	// Store original position
	sf::Vector2f originalPosition = entity->getPosition();

	for (auto& obj : enemies) {
		Side Type = CollisionType(entity, obj);
		if (Type != Collide_None) {
			// When pushed by enemy, don't modify Mario's position if it would cause block penetration
			sf::Vector2f proposedPosition = entity->getPosition();
			fixPosition(entity, obj, Type);

			// Check if new position would cause block penetration
			bool willPenetrate = false;
			for (auto& block : blocks) { 
				if (CollisionType(entity, block) != Collide_None) {
					willPenetrate = true;
					break;
				}
			}

			if (willPenetrate) {
				entity->setPosition(proposedPosition);
				entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			}

			switch (Type) {
			case Collide_Right:
				obj->reactToPlayerCollision(Collide_Left);
				break;
			case Collide_Left:
				obj->reactToPlayerCollision(Collide_Right);
				break;
			case Collide_Bottom:
				entity->movementComponent->resetJumps();
				obj->reactToPlayerCollision(Collide_Top);
				break;
			case Collide_Top:
				obj->reactToPlayerCollision(Collide_Bottom);
				break;
			}
		}
	}
}

void PhysicsEngine::resolveCollisionEnemyBlock(std::vector<Enemy*>& enemies, std::vector<Block*>& blocks, const float& dt) {
	for (auto& enemy : enemies) {
		for (auto& block : blocks) {
			//Resolve the right side
			Side Type = CollisionType(enemy, block);
			
			switch (Type) {
			case (Collide_Right):
				fixPosition(enemy, block, Collide_Right);
				enemy->reactToBlockCollision(Collide_Right);
				break;

				//Resolve the left side
			case (Collide_Left):
				fixPosition(enemy, block, Collide_Left);
				enemy->reactToBlockCollision(Collide_Left);
				enemy->setScaleSprite("RIGHT");
				break;

				//Resolve the ground
			case (Collide_Bottom):
				fixPosition(enemy, block, Collide_Bottom);
				enemy->setVelocity(sf::Vector2f(enemy->getVelocity().x, -10.0f));
				enemy->reactToBlockCollision(Collide_Bottom);
				break;

				//Resolve the ceiling
			case (Collide_Top):
				fixPosition(enemy, block, Collide_Top);
				enemy->reactToBlockCollision(Collide_Top);
				break;
			}
		}
	}
}

void PhysicsEngine::resolveCollisionPlayerPowerUp(PlayerManager* entity, std::vector<PowerUpObject*>& PowerUps, const float& dt) {
	for (auto& obj : PowerUps) {
		Side Type = CollisionType(entity, obj);
		if (Type != Collide_None) {
			obj->reactToCollison();
		}
	}
}

void PhysicsEngine::resolveCollisionEnemyEnemy(std::vector<Enemy*>& enemies, const float& dt) {
	for (size_t i = 0; i < enemies.size(); ++i) {
		for (size_t j = i + 1; j < enemies.size(); ++j) {
			Enemy* enemy1 = enemies[i];
			Enemy* enemy2 = enemies[j];

			Side Type = CollisionType(enemy1, enemy2);

			// Skip if either enemy is not alive
			if (!enemy1->getIsAlive() || !enemy2->getIsAlive()) {
				continue;
			}

			//Resolve the right side
			if (enemy1->isMoveRight() && Type == Collide_Right) {
				fixPosition(enemy1, enemy2, Collide_Right);
				enemy1->setMoveRight(false);
				enemy1->setMoveLeft(true);

				enemy1->setScaleSprite("LEFT");

				enemy2->setMoveRight(true);
				enemy2->setMoveLeft(false);

				enemy2->setScaleSprite("RIGHT");

				continue;
			}

			//Resolve the left side
			if (enemy1->isMoveLeft() && Type == Collide_Left) {
				fixPosition(enemy1, enemy2, Collide_Left);
				enemy1->setMoveLeft(false);
				enemy1->setMoveRight(true);

				enemy1->setScaleSprite("RIGHT");

				enemy2->setMoveRight(false);
				enemy2->setMoveLeft(true);

				enemy2->setScaleSprite("LEFT");

				continue;
			}

			//Resolve the ground
			if (enemy1->getVelocity().y >= 0 && Type == Collide_Bottom) {
				fixPosition(enemy1, enemy2, Collide_Bottom);
				continue;
			}

			//Resolve the ceiling
			if (enemy1->getVelocity().y < 0 && Type == Collide_Top) {
				fixPosition(enemy1, enemy2, Collide_Top);
				continue;
			}
		}
	}
}

void PhysicsEngine::applyExternalForces(LivingEntity* entity, const float& dt) {
	applyGravity(entity, dt);
	applyFriction(entity, dt);
}