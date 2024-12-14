#include "Headers/PhysicsEngine.h"
#include "Headers/GameEventMediator.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/LivingEntity.h"
#include "Headers/Enemy.h"
#include "Headers/PowerUpObject.h"

PhysicsEngine::PhysicsEngine() {
	gravity = sf::Vector2f(0, 2.0f * PIXELS_PER_METER);
	friction = sf::Vector2f(1.0f * PIXELS_PER_METER, 0);
}

void PhysicsEngine::setEventMediator(GameEventMediator* mediator) {
	this->eventMediator = mediator;
}

void PhysicsEngine::applyGravity(LivingEntity* entity, const float& dt) {
	entity->setVelocity(entity->getVelocity() + gravity * dt);
	entity->setVelocity(sf::Vector2f(entity->getVelocity().x, std::min(entity->getVelocity().y, 15.0f * PIXELS_PER_METER)));
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

bool PhysicsEngine::checkCollision(GameObject* obj1, GameObject* obj2) {
	if (obj1->hitbox.getGlobalBounds().getPosition().x > obj2->hitbox.getGlobalBounds().getPosition().x + obj2->hitbox.getSize().x ||
		obj1->hitbox.getGlobalBounds().getPosition().x + obj1->hitbox.getSize().x < obj2->hitbox.getGlobalBounds().getPosition().x) {
		return false;
	}
	if (obj1->hitbox.getGlobalBounds().getPosition().y > obj2->hitbox.getGlobalBounds().getPosition().y + obj2->hitbox.getSize().y ||
		obj1->hitbox.getGlobalBounds().getPosition().y + obj1->hitbox.getSize().y < obj2->hitbox.getGlobalBounds().getPosition().y) {
		return false;
	}
	return true;
}

bool PhysicsEngine::checkCollideDown(GameObject* obj1, GameObject* obj2) {
	if (obj2->hitbox.getGlobalBounds().getPosition().x >= obj1->hitbox.getGlobalBounds().getPosition().x + obj1->hitbox.getSize().x - 2 ||
		obj2->hitbox.getGlobalBounds().getPosition().x + obj2->hitbox.getSize().x <= obj1->hitbox.getGlobalBounds().getPosition().x + 2) {
		return false;
	}

	// Check if object2 is below object1
	if (obj2->hitbox.getGlobalBounds().getPosition().y >= obj1->hitbox.getGlobalBounds().getPosition().y + obj1->hitbox.getSize().y) {
		return false;
	}

	if (!checkCollision(obj1, obj2)) {
		return false;
	}
	return true;
}

bool PhysicsEngine::checkCollideUp(GameObject* obj1, GameObject* obj2) {
	if (obj2->hitbox.getGlobalBounds().getPosition().x >= obj1->hitbox.getGlobalBounds().getPosition().x + obj1->hitbox.getSize().x - 2 ||
		obj2->hitbox.getGlobalBounds().getPosition().x + obj2->hitbox.getSize().x <= obj1->hitbox.getGlobalBounds().getPosition().x + 2) {
		return false;
	}

	// Check if the object1 is below object2 and they collide
	return ((obj2->hitbox.getPosition().y <= obj1->hitbox.getPosition().y) && checkCollision(obj1, obj2));
}

bool PhysicsEngine::checkCollideLeft(GameObject* obj1, GameObject* obj2) {
	if (obj2->hitbox.getGlobalBounds().getPosition().y >= obj1->hitbox.getGlobalBounds().getPosition().y + obj1->hitbox.getSize().y - 2 ||
		obj2->hitbox.getGlobalBounds().getPosition().y + obj2->hitbox.getSize().y <= obj1->hitbox.getGlobalBounds().getPosition().y + 2) {
		return false;
	}

	// Check if the object is to the left of the entity and they collide
	return (obj2->hitbox.getGlobalBounds().getPosition().x + 2 <= obj1->hitbox.getGlobalBounds().getPosition().x && checkCollision(obj1, obj2));
}

bool PhysicsEngine::checkCollideRight(GameObject* obj1, GameObject* obj2) {
	if (obj2->hitbox.getGlobalBounds().getPosition().y >= obj1->hitbox.getGlobalBounds().getPosition().y + obj1->hitbox.getSize().y - 2 ||
		obj2->hitbox.getGlobalBounds().getPosition().y + obj2->hitbox.getSize().y <= obj1->hitbox.getGlobalBounds().getPosition().y + 2) {
		return false;
	}

	// Check if the object is to the right of the entity and they collide
	return (obj2->hitbox.getGlobalBounds().getPosition().x >= obj1->hitbox.getGlobalBounds().getPosition().x + 2 && checkCollision(obj1, obj2));
}

void PhysicsEngine::fixPosition(LivingEntity* entity, GameObject* obj, int collidedSide) {
	switch (collidedSide) {
	case Collide_Top:
		while (checkCollision(entity, obj)) {
			entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + 1));
		}
		entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
		break;
	case Collide_Bottom:
		entity->setOnGround(true);
		while (checkCollision(entity, obj))
		{
			entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - 1));
		}
		entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + 0.5));
		entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
		entity->movementComponent->resetJumps();
		break;
	case Collide_Left:
		while (checkCollision(entity, obj)) {
			entity->setPosition(sf::Vector2f(entity->getPosition().x + 1, entity->getPosition().y));
		}
		entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
		break;
	case Collide_Right:
		while (checkCollision(entity, obj)) {
			entity->setPosition(sf::Vector2f(entity->getPosition().x - 1, entity->getPosition().y));
		}
		entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
		break;
	}
}


void PhysicsEngine::resolveCollisionPlayerBlock(PlayerManager* entity, std::vector<Block*>& blocks, const float& dt) {
	// Resolve on the ground
	entity->setOnGround(false);

	for (auto& obj : blocks) {
		//Resolve the right side

		if (entity->isMoveRight() && checkCollideRight(entity, obj)) {
			fixPosition(entity, obj, Collide_Right);
			// std::cout << "Mario Collide Right\n";
			obj->reactToCollison(Collide_Left);
			continue;
		}

		//Resolve the left side
		if (entity->isMoveLeft() && checkCollideLeft(entity, obj)) {
			fixPosition(entity, obj, Collide_Left);
			// std::cout << "Mario Collide Left\n";

			obj->reactToCollison(Collide_Right);
			continue;
		}

		//Resolve the ground
		if (entity->getVelocity().y >= 0 && checkCollideDown(entity, obj)) {
			fixPosition(entity, obj, Collide_Bottom);
			obj->reactToCollison(Collide_Top);
			continue;
		}

		//Resolve the ceiling
		if (entity->getVelocity().y < 0 && checkCollideUp(entity,obj)) {
			fixPosition(entity, obj, Collide_Top);
			// std::cout << "Collide Up\n";
			obj->reactToCollison(Collide_Bottom);
			continue;
		}

		
	}
}

void PhysicsEngine::resolveCollisionPlayerEnemy(PlayerManager* entity, std::vector<Enemy*>& enemies, const float& dt) {
	for (auto &obj : enemies) {
		//Resolve the right side
		if (entity->isMoveRight() && checkCollideRight(entity, obj)) {
			fixPosition(entity, obj, Collide_Right);
			obj->reactToPlayerCollision(Collide_Left);
			 //Testing
			
			continue;
		}

		//Resolve the left side
		if (entity->isMoveLeft() && checkCollideLeft(entity, obj)) {
			fixPosition(entity, obj, Collide_Left);
			obj->reactToPlayerCollision(Collide_Right);
			
			continue;
		}

		//Resolve the ground
		if (entity->getVelocity().y >= 0 && checkCollideDown(entity, obj)) {
			fixPosition(entity, obj, Collide_Bottom);
			obj->reactToPlayerCollision(Collide_Top);
			continue;
		}

		//Resolve the ceiling
		if (entity->getVelocity().y < 0 && checkCollideUp(entity, obj)) {
			fixPosition(entity, obj, Collide_Top);
			obj->reactToPlayerCollision(Collide_Bottom);
			
			continue;
		}
	}
}

void PhysicsEngine::resolveCollisionEnemyBlock(std::vector<Enemy*>& enemies, std::vector<Block*>& blocks, const float& dt) {
	for (auto &enemy : enemies) {
		for (auto &block : blocks) {
			//Resolve the right side
			if (enemy->isMoveRight() && checkCollideRight(enemy, block)) {
				fixPosition(enemy, block, Collide_Right);
				//enemy->reactToBlockCollison(Collide_Right);
				enemy->setMoveRight(false);
				enemy->setMoveLeft(true);

				
				enemy->setScaleSprite("LEFT");


				continue;
			}

			//Resolve the left side
			if (enemy->isMoveLeft() && checkCollideLeft(enemy, block)) {
				fixPosition(enemy, block, Collide_Left);
				//enemy->reactToBlockCollison(Collide_Left);
				enemy->setMoveLeft(false);
				enemy->setMoveRight(true);

				enemy->setScaleSprite("RIGHT");

				continue;
			}

			//Resolve the ground
			if (enemy->getVelocity().y >= 0 && checkCollideDown(enemy, block)) {
				fixPosition(enemy, block, Collide_Bottom);
				//enemy->reactToBlockCollison(Collide_Bottom);

				continue;
			}

			//Resolve the ceiling
			if (enemy->getVelocity().y < 0 && checkCollideUp(enemy, block)) {
				fixPosition(enemy, block, Collide_Top);
				//enemy->reactToBlockCollison(Collide_Top);

				continue;
			}
		}
	}
}

void PhysicsEngine::resolveCollisionPlayerPowerUp(PlayerManager* entity, std::vector<PowerUpObject*>& PowerUps, const float& dt) {
	for (auto& obj : PowerUps) {
		//If the player collides with the powerup, the power up applies
		if (checkCollision(entity, obj)) {
			obj->reactToCollison();
		}
	}
}

void PhysicsEngine::resolveCollisionEnemyEnemy(std::vector<Enemy*>& enemies, const float& dt) {
	for (size_t i = 0; i < enemies.size(); ++i) {
		for (size_t j = i + 1; j < enemies.size(); ++j) {
			Enemy* enemy1 = enemies[i];
			Enemy* enemy2 = enemies[j];

			// Skip if either enemy is not alive
			if (!enemy1->getIsAlive() || !enemy2->getIsAlive()) {
				continue;
			}

			//Resolve the right side
			if (enemy1->isMoveRight() && checkCollideRight(enemy1, enemy2)) {
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
			if (enemy1->isMoveLeft() && checkCollideLeft(enemy1, enemy2)) {
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
			if (enemy1->getVelocity().y >= 0 && checkCollideDown(enemy1, enemy2)) {
				fixPosition(enemy1, enemy2, Collide_Bottom);
				continue;
			}

			//Resolve the ceiling
			if (enemy1->getVelocity().y < 0 && checkCollideUp(enemy1, enemy2)) {
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