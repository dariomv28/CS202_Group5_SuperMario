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

void PhysicsEngine::resolveCollision(LivingEntity* entity) {
	// Resolve on the ground
	entity->setOnGround(false);

	// Remove later when there is a ground
	//if (entity->getPosition().y + entity->getSize().y >= 800) {
	//	entity->setOnGround(true);
	//	entity->setPosition(sf::Vector2f(entity->getPosition().x, 800 - entity->getSize().y));
	//	entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
	//	entity->movementComponent->resetJumps();  // Reset jumps when landing
	//}

	// Check for ground collision when moving downward
	if (entity->getVelocity().y > 0) {
		for (auto obj : blocks) {
			// Check if the x-coordinate of the object 
			// is in the range [entity->getPosition().x, entity->getPosition().x + entity->getSize().x]
			if (obj->getPosition().x >= entity->getPosition().x + entity->getSize().x-1 ||
				obj->getPosition().x + obj->getSize().x <= entity->getPosition().x+1) {
				continue;
			}

			// Check if the object is below the entity
			if (!entity->checkCollision(obj)) {
				continue;
			}
			entity->setOnGround(true);
			while (entity->getPosition().y + entity->getSize().y >= obj->getPosition().y) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - 1));
			}
			entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y));
			entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
			entity->movementComponent->resetJumps();
			break;
		}
	}
	 
	// Resolve hitting the ceiling
	if (entity->getVelocity().y < 0) {
		for (auto obj : blocks) {
			if (entity->checkCollisionUp(obj)) {	
				while (entity->checkCollisionUp(obj)) {
					entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y + 1));
				}
				entity->setPosition(sf::Vector2f(entity->getPosition().x, entity->getPosition().y - 1));
				entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
				//entity->movementComponent->resetJumps();
				//break;
			}
		}
	}
	// Resolve right side collision
	if (entity->isMoveRight()) {
		for (auto obj : blocks) {
			//check if the object is in the range of the entity
			if (obj->getPosition().y >= entity->getPosition().y + entity->getSize().y - 1 ||
				obj->getPosition().y + obj->getSize().y <= entity->getPosition().y + 1) {
				continue;
			}
			if (!entity->checkCollision(obj)) {
				continue;
			}
			while (entity->checkCollision(obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x - 1, entity->getPosition().y));
			}
			entity->setPosition(sf::Vector2f(entity->getPosition().x + 1, entity->getPosition().y));
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			break;
		}
	}

	// Resolve left side collision
	if (entity->isMoveLeft()) {
		for (auto obj : blocks) {
			//check if the object is in the range of the entity
			if (obj->getPosition().y >= entity->getPosition().y + entity->getSize().y - 1 ||
				obj->getPosition().y + obj->getSize().y <= entity->getPosition().y + 1) {
				continue;
			}
			if (!entity->checkCollision(obj)) {
				continue;
			}
			while (entity->checkCollision(obj)) {
				entity->setPosition(sf::Vector2f(entity->getPosition().x + 1, entity->getPosition().y));
			}
			entity->setPosition(sf::Vector2f(entity->getPosition().x - 1, entity->getPosition().y));
			entity->setVelocity(sf::Vector2f(0, entity->getVelocity().y));
			break;
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
