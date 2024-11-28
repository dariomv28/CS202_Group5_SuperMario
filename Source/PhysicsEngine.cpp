#include "Headers/PhysicsEngine.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/LivingEntity.h"
#include "Headers/Enemy.h"

PhysicsEngine::PhysicsEngine() {
	gravity = sf::Vector2f(0, 2.0f * PIXELS_PER_METER);
	friction = sf::Vector2f(15.0f * PIXELS_PER_METER, 0);
	player = nullptr;
}

void PhysicsEngine::addBlock(Block* obj) {
	blocks.push_back(obj);
}

void PhysicsEngine::addPlayer(PlayerManager* obj) {
	player = obj;
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
	if (obj1->getPosition().x > obj2->getPosition().x + obj2->getSize().x ||
		obj1->getPosition().x + obj1->getSize().x < obj2->getPosition().x) {
		return false;
	}
	if (obj1->getPosition().y > obj2->getPosition().y + obj2->getSize().y ||
		obj1->getPosition().y + obj1->getSize().y < obj2->getPosition().y) {
		return false;
	}
	return true;
}

bool PhysicsEngine::checkCollideDown(GameObject* obj1, GameObject* obj2) {
	if (obj2->getPosition().x >= obj1->getPosition().x + obj1->getSize().x - 8 ||
		obj2->getPosition().x + obj2->getSize().x <= obj1->getPosition().x + 8) {
		return false;
	}

	// Check if object2 is below object1
	if (obj2->getPosition().y >= obj1->getPosition().y + obj1->getSize().y) {
		return false;
	}

	if (!checkCollision(obj1, obj2)) {
		return false;
	}
	return true;
}

bool PhysicsEngine::checkCollideUp(GameObject* obj1, GameObject* obj2) {
	if (obj2->getPosition().x >= obj1->getPosition().x + obj1->getSize().x - 8 ||
		obj2->getPosition().x + obj2->getSize().x <= obj1->getPosition().x + 8) {
		return false;
	}

	// Check if the object1 is below object2 and they collide
	return ((obj2->getPosition().y <= obj1->getPosition().y) && checkCollision(obj1, obj2));
}

bool PhysicsEngine::checkCollideLeft(GameObject* obj1, GameObject* obj2) {
	if (obj2->getPosition().y >= obj1->getPosition().y + obj1->getSize().y - 8 ||
		obj2->getPosition().y + obj2->getSize().y <= obj1->getPosition().y + 8) {
		return false;
	}

	// Check if the object is to the left of the entity and they collide
	return (obj2->getPosition().x + 8 <= obj1->getPosition().x && checkCollision(obj1, obj2));
}

bool PhysicsEngine::checkCollideRight(GameObject* obj1, GameObject* obj2) {
	if (obj2->getPosition().y >= obj1->getPosition().y + obj1->getSize().y - 8 ||
		obj2->getPosition().y + obj2->getSize().y <= obj1->getPosition().y + 8) {
		return false;
	}

	// Check if the object is to the right of the entity and they collide
	return (obj2->getPosition().x >= obj1->getPosition().x + 8 && checkCollision(obj1, obj2));	
}


void PhysicsEngine::resolveCollision(LivingEntity* entity) {
	// Resolve on the ground
	entity->setOnGround(false);

	for (auto obj : blocks) {
		//Resolve the right side

		if (entity->isMoveRight() && checkCollideRight(entity, obj)) {
			while (checkCollision(entity, obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x - 1, entity->getPosition().y));
			}
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			continue;
		}

		//Resolve the left side
		if (entity->isMoveLeft() && checkCollideLeft(entity, obj)) {
			while (checkCollision(entity, obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x + 1, entity->getPosition().y));
			}
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			continue;
		}

		//Resolve the ground
		if (entity->getVelocity().y >= 0 && checkCollideDown(entity, obj)) {
			entity->setOnGround(true);
			while (checkCollision(entity,obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - 1));
			}
			//entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + 1));

			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
			entity->movementComponent->resetJumps();
			continue;
		}

		//Resolve the ceiling
		if (entity->getVelocity().y < 0 && checkCollideUp(entity,obj)) {
			while (checkCollision(entity, obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + 1));
			}
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
			continue;
		}

		
	}
}

void PhysicsEngine::applyExternalForces(LivingEntity* entity, const float& dt) {
	applyGravity(entity, dt);
	applyFriction(entity, dt);
}

//void PhysicsEngine::updateMovement(LivingEntity* entity, const float& dt) {
//	//Apply external forces
//	applyExternalForces(entity, dt);
//
//	//Move the entity
//	entity->setPosition(entity->getPosition() + entity->getVelocity() );
//	
//	//Resolve collisions
//	resolveCollision(entity);
//}

//void PhysicsEngine::playerUpdatePhysics(const float& dt) {
//	updateMovement(player, dt);
//}
//
//void PhysicsEngine::objectUpdatePhysics(const float& dt) {
//
//}
