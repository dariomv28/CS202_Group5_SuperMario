#include "Headers/PhysicsEngine.h"
#include "Headers/GameEventMediator.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/LivingEntity.h"
#include "Headers/Enemy.h"
#include "Headers/PowerUpObject.h"

PhysicsEngine::PhysicsEngine() {
	gravity = sf::Vector2f(0, 1000.f);
	friction = sf::Vector2f(500.f, 0);
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
		else return (dx <= 0) ? Side::Collide_Left : Side::Collide_Right;
	}
	else return Side::Collide_None;
}

void PhysicsEngine::fixPosition(LivingEntity* entity, GameObject* obj, Side collidedSide) {
	//std::cerr << "velocity: " << entity->getVelocity().x << " " << entity->getVelocity().y << "\n";
	switch (collidedSide) {
	case Collide_Top:
		entity->setPosition(sf::Vector2f(entity->getPosition().x, obj->getPosition().y + obj->getSize().y));
		break;
	case Collide_Bottom:
		entity->setPosition(sf::Vector2f(entity->getPosition().x, obj->getPosition().y - entity->getSize().y));
		break;
	case Collide_Left:
		entity->setPosition(sf::Vector2f(obj->getPosition().x + obj->getSize().x,entity->getPosition().y));
		break;
	case Collide_Right:
		entity->setPosition(sf::Vector2f(obj->getPosition().x - entity->getSize().x, entity->getPosition().y));
		break;
	}
}


//void PhysicsEngine::fixPosition(LivingEntity* entity, std::vector<Block*> Collided_Blocks[]) {
//
//		float top = entity->getPosition().y, bottom = entity->getPosition().y + entity->getSize().y,
//		left = entity->getPosition().x, right = entity->getPosition().x + entity->getSize().x;// Bottom
//	
//	//std::cerr << "Before: " << top << " " << bottom << " " << left << " " << right << std::endl;
//	for (auto& obj : Collided_Blocks[0])
//	{
//		bottom = std::min(bottom, obj->getPosition().y);
//	}
//
//	// top
//	for (auto& obj : Collided_Blocks[1])
//	{
//		top = std::max(top, obj->getPosition().y + obj->getSize().y);
//	}
//
//	// Left
//	for (auto& obj : Collided_Blocks[2])
//	{
//		left = std::max(left, obj->getPosition().x + obj->getSize().x);
//	}
//
//	// Right
//	for (auto& obj : Collided_Blocks[3])
//	{
//		right = std::min(right, obj->getPosition().x);
//	}
//	
//	// resolve
//	if (Collided_Blocks[1].size() != 0)
//	{
//		entity->setPosition(entity->getPosition().x, top);
//		if (Collided_Blocks[2].size() != 0)
//		{
//			entity->setPosition(left, top);
//		}
//		else if (Collided_Blocks[3].size() != 0)
//		{
//			entity->setPosition(right - entity->getSize().x, top);
//		}
//	}
//	else if (Collided_Blocks[0].size() != 0)
//	{
//		//std::cerr << "Fixing: " << entity->getPosition().x << " " << left << std::endl;
//		entity->setPosition(entity->getPosition().x, bottom - entity->getSize().y);
//		if (Collided_Blocks[2].size() != 0)
//		{
//			entity->setPosition(left, bottom - entity->getSize().y);
//		}
//		else if (Collided_Blocks[3].size() != 0)
//		{
//			entity->setPosition(right - entity->getSize().x, bottom - entity->getSize().y);
//		}
//	}
//}


void PhysicsEngine::resolveCollisionPlayerBlock(PlayerManager* entity, std::vector<Block*>& blocks, const float& dt) {
	// Resolve on the ground
	entity->setOnGround(false);
	std::vector<Block*> Blocks_Collide[4]; 
	/*0 is Bottom
	1 is Top
	2 is Left
	3 is Right*/

	for (auto& obj : blocks)
	{
		if (obj->getExist() == false) continue;

		//Resolve the right side
		Side Type = CollisionType(entity, obj);
		if (Type != Collide_None) fixPosition(entity, obj, Type);
		switch (Type) {
		case (Collide_Bottom):
			Blocks_Collide[0].push_back(obj);
			//fixPosition(entity, obj, Collide_Bottom);
			entity->setOnGround(true);
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
			entity->movementComponent->resetJumps();
			//std::cerr << "Collide Bottom\n";
			continue;
		case (Collide_Top):
			Blocks_Collide[1].push_back(obj);
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
			//std::cerr << "Collide Top\n";
			continue;

		case (Collide_Right):
			Blocks_Collide[3].push_back(obj);
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			entity->setMoveRight(false);
			//std::cerr << "Collide Right\n";
			continue;
		case (Collide_Left):
			Blocks_Collide[2].push_back(obj);
 			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			entity->setMoveLeft(false);
			//std::cerr << "Collide Left\n";
			continue;
		}
	}

	//std::cerr << entity->getVelocity().x << std::endl;
	//fixPosition(entity, Blocks_Collide);
	

}

void PhysicsEngine::resolveCollisionPlayerEnemy(PlayerManager* entity, std::vector<Enemy*>& enemies, const float& dt) {
	//for (auto& obj : enemies) {
	//	//Resolve the right side
	//	Side Type = CollisionType(entity, obj);

	//	if (entity->isMoveRight() && Type == Collide_Right) {
	//		fixPosition(entity, obj, Collide_Right);
	//		obj->reactToPlayerCollision(Collide_Left);
	//		//Testing


	//		continue;
	//	}

	//	//Resolve the left side
	//	if (entity->isMoveLeft() && Type == Collide_Left) {
	//		fixPosition(entity, obj, Collide_Left);
	//		obj->reactToPlayerCollision(Collide_Right);

	//		continue;
	//	}

	//	//Resolve the ground
	//	if (entity->getVelocity().y >= 0 && Type == Collide_Bottom) {
	//		fixPosition(entity, obj, Collide_Bottom);
	//		obj->reactToPlayerCollision(Collide_Top);
	//		continue;
	//	}

	//	//Resolve the ceiling
	//	if (entity->getVelocity().y < 0 && Type == Collide_Top) {
	//		fixPosition(entity, obj, Collide_Top);
	//		obj->reactToPlayerCollision(Collide_Bottom);

	//		continue;
	//	}
	//}
}

void PhysicsEngine::resolveCollisionEnemyBlock(std::vector<Enemy*>& enemies, std::vector<Block*>& blocks, const float& dt) {
	//for (auto& enemy : enemies) {
	//	for (auto& block : blocks) {
	//		//Resolve the right side
	//		Side Type = CollisionType(enemy, block);

	//		if (enemy->isMoveRight() && Type == Collide_Right) {
	//			fixPosition(enemy, block, Collide_Right);
	//			//enemy->reactToBlockCollison(Collide_Right);
	//			enemy->setMoveRight(false);
	//			enemy->setMoveLeft(true);


	//			enemy->setScaleSprite("LEFT");


	//			continue;
	//		}

	//		//Resolve the left side
	//		if (enemy->isMoveLeft() && Type == Collide_Left) {
	//			fixPosition(enemy, block, Collide_Left);
	//			//enemy->reactToBlockCollison(Collide_Left);
	//			enemy->setMoveLeft(false);
	//			enemy->setMoveRight(true);

	//			enemy->setScaleSprite("RIGHT");

	//			continue;
	//		}

	//		//Resolve the ground
	//		if (enemy->getVelocity().y >= 0 && Type == Collide_Bottom) {
	//			fixPosition(enemy, block, Collide_Bottom);
	//			//enemy->reactToBlockCollison(Collide_Bottom);

	//			continue;
	//		}

	//		//Resolve the ceiling
	//		if (enemy->getVelocity().y < 0 && Type == Collide_Top) {
	//			fixPosition(enemy, block, Collide_Top);
	//			//enemy->reactToBlockCollison(Collide_Top);

	//			continue;
	//		}
	//	}
	//}
}

void PhysicsEngine::resolveCollisionPlayerPowerUp(PlayerManager* entity, std::vector<PowerUpObject*>& PowerUps, const float& dt) {
	for (auto& obj : PowerUps) {
		//If the player collides with the powerup, the power up applies
//<<<<<<< HEAD
		Side Type = CollisionType(entity, obj);
		if (Type != Collide_None) {
			obj->reactToCollison();
		}
	}
}

void PhysicsEngine::resolveCollisionEnemyEnemy(std::vector<Enemy*>& enemies, const float& dt) {
	//for (size_t i = 0; i < enemies.size(); ++i) {
	//	for (size_t j = i + 1; j < enemies.size(); ++j) {
	//		Enemy* enemy1 = enemies[i];
	//		Enemy* enemy2 = enemies[j];

	//		Side Type = CollisionType(enemy1, enemy2);

	//		// Skip if either enemy is not alive
	//		if (!enemy1->getIsAlive() || !enemy2->getIsAlive()) {
	//			continue;
	//		}

	//		//Resolve the right side
	//		if (enemy1->isMoveRight() && Type == Collide_Right) {
	//			fixPosition(enemy1, enemy2, Collide_Right);
	//			enemy1->setMoveRight(false);
	//			enemy1->setMoveLeft(true);

	//			enemy1->setScaleSprite("LEFT");

	//			enemy2->setMoveRight(true);
	//			enemy2->setMoveLeft(false);

	//			enemy2->setScaleSprite("RIGHT");

	//			continue;
	//		}

	//		//Resolve the left side
	//		if (enemy1->isMoveLeft() && Type == Collide_Left) {
	//			fixPosition(enemy1, enemy2, Collide_Left);
	//			enemy1->setMoveLeft(false);
	//			enemy1->setMoveRight(true);

	//			enemy1->setScaleSprite("RIGHT");

	//			enemy2->setMoveRight(false);
	//			enemy2->setMoveLeft(true);

	//			enemy2->setScaleSprite("LEFT");

	//			continue;
	//		}

	//		//Resolve the ground
	//		if (enemy1->getVelocity().y >= 0 && Type == Collide_Bottom) {
	//			fixPosition(enemy1, enemy2, Collide_Bottom);
	//			continue;
	//		}

	//		//Resolve the ceiling
	//		if (enemy1->getVelocity().y < 0 && Type == Collide_Top) {
	//			fixPosition(enemy1, enemy2, Collide_Top);
	//			continue;
	//		}
	//	}
	//}
}

void PhysicsEngine::applyExternalForces(LivingEntity* entity, const float& dt) {
	applyGravity(entity, dt);
	applyFriction(entity, dt);
}