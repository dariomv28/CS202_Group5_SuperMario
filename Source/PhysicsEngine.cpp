#include "Headers/PhysicsEngine.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/LivingEntity.h"
#include "Headers/Enemy.h"
#include <iostream>

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
	return obj1->hitbox.getGlobalBounds().intersects(obj2->hitbox.getGlobalBounds());
}

bool PhysicsEngine::checkOnGround(GameObject* obj1, GameObject* obj2) {
	if (obj2->getPosition().x >= obj1->getPosition().x + obj1->getSize().x - 1 ||
		obj2->getPosition().x + obj2->getSize().x <= obj1->getPosition().x + 1) {
		return false;
	}

	// Check if the object is below the entity
	if (obj2->getPosition().y >= obj1->getPosition().y + obj1->getSize().y) {
		return false;
	}

	if (!checkCollision(obj1, obj2)) {
		return false;
	}
	return true;
}

bool PhysicsEngine::checkCeiling(GameObject* obj1, GameObject* obj2) {
	if (obj2->getPosition().x >= obj1->getPosition().x + obj1->getSize().x - 1 ||
		obj2->getPosition().x + obj2->getSize().x <= obj1->getPosition().x + 1) {
		return false;
	}

	// Check if the object1 is below object2 
	if (!(obj2->getPosition().y <= obj1->getPosition().y))  {
		return false;
	}
	
	if (!checkCollision(obj1, obj2)) {
		return false;
	}
	std::cout << "Collision detected" << std::endl;
	return true;
}


void PhysicsEngine::resolveCollision(LivingEntity* entity) {
	// Resolve on the ground
	entity->setOnGround(false);

	for (auto obj : blocks) {
		//Resolve the ground
		if (entity->getVelocity().y >= 0 && checkOnGround(entity, obj)) {
			entity->setOnGround(true);
			while (checkCollision(entity,obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - 1));
			}
			//entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y));
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
			entity->movementComponent->resetJumps();
			continue;
		}
		//Resolve the ceiling
		if (entity->getVelocity().y < 0 && checkCeiling(entity,obj)) {
		
			while (checkCollision(entity, obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + 1));
			}
			//entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + 1));
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
			continue;
			//break;
		}

		if (entity->isMoveRight()) {
			if (!(obj->getPosition().y >= entity->getPosition().y + entity->getSize().y-2 ||
				obj->getPosition().y + obj->getSize().y <= entity->getPosition().y+2) && 
				obj->getPosition().x >= entity->getPosition().x) {
				if (checkCollision(entity, obj)) {
					while (checkCollision(entity, obj)) {
						entity->setPosition(sf::Vector2f(entity->getPosition().x - 1, entity->getPosition().y));
					}
					entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));

				}
			}
			//entity->setPosition(sf::Vector2f(entity->getPosition().x + 1, entity->getPosition().y));
			//break;
		}

		if (entity->isMoveLeft()) {
			if (obj->getPosition().y >= entity->getPosition().y + entity->getSize().y ||
				obj->getPosition().y + obj->getSize().y <= entity->getPosition().y) {
				continue;
			}
			//check if the object is to the left of the entity
			if (obj->getPosition().x >= entity->getPosition().x + entity->getSize().x) {
				continue;
			}
			if (!checkCollision(entity, obj)) {
				continue;
			}
			while (checkCollision(entity, obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x + 1, entity->getPosition().y));
			}
			//entity->setPosition(sf::Vector2f(entity->getPosition().x - 1, entity->getPosition().y));
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			//break;
		}
	}


}

void PhysicsEngine::updateMovement(LivingEntity* entity, const float& dt) {
	resolveCollision(entity);
	if (!entity->getOnGround()) {
		applyGravity(entity, dt);
	}
	applyFriction(entity, dt);
}

void PhysicsEngine::playerUpdatePhysics(const float& dt) {
	updateMovement(player, dt);
}

void PhysicsEngine::objectUpdatePhysics(const float& dt) {

}
