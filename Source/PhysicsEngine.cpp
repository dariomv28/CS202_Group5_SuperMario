#include "Headers/PhysicsEngine.h"
#include "Headers/PlayerManager.h"
#include "Headers/GameObject.h"
#include "Headers/LivingEntity.h"
#include "Headers/Enemy.h"

PhysicsEngine::PhysicsEngine() {
	gravity = sf::Vector2f(0, 2.0f * PIXELS_PER_METER);
	friction = sf::Vector2f(15.0f * PIXELS_PER_METER, 0);
	player = nullptr;
}

void PhysicsEngine::addObject(GameObject* obj) {
	objects.push_back(obj);
}

void PhysicsEngine::addPlayer(PlayerManager* obj) {
	player = obj;
}

void PhysicsEngine::applyGravity(LivingEntity* entity, const float& dt) {
	entity->setVelocity(entity->getVelocity() + gravity * dt);
	//const float maxFallSpeed = 3.0f * PIXELS_PER_METER;
	//if (entity->getVelocity().y > maxFallSpeed) {
	//	entity->setVelocity(sf::Vector2f(entity->getVelocity().x, maxFallSpeed));
	//}
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

	//Remove later when there is a ground
	if (entity->getPosition().y + entity->getSize().y >= 828) {
		entity->setOnGround(true);
		entity->setPosition(sf::Vector2f(entity->getPosition().x, 828 - entity->getSize().y));
		entity->movementComponent->resetJumps();  // Reset jumps when landing
	}

	if (entity->getVelocity().y > 0) {
		for (auto obj : objects) {
			if (entity->checkCollisionDown(*obj)) {
				entity->setOnGround(true);
				entity->movementComponent->resetJumps();  // Reset jumps when landing on objects
				break;
			}	
		}
	}

	// Resolve hitting the ceiling
	if (entity->getVelocity().y < 0) {
		for (auto obj : objects) {
			if (entity->checkCollisionUp(*obj)) {	
				entity->setVelocity(sf::Vector2f(entity->getVelocity().x, 0));
				break;
			}
		}
	}
	// Resolve right side collision
	if (entity->isMoveRight()) {
		for (auto obj : objects) {
			if (entity->checkCollisionRight(*obj)) {
				entity->setMoveRight(false);
				break;
			}
		}
	}

	// Resolve left side collision
	if (entity->isMoveLeft()) {
		for (auto obj : objects) {
			if (entity->checkCollisionLeft(*obj)) {
				entity->setMoveLeft(false);
				break;
			}
		}
	}

}

void PhysicsEngine::updateMovement(LivingEntity* entity, const float& dt) {
	resolveCollision(entity);
	if (!entity->getOnGround()) //{
		applyGravity(entity, dt);
//	} else {
		applyFriction(entity, dt);
	//}
}

void PhysicsEngine::playerUpdatePhysics(const float& dt) {
	updateMovement(player, dt);
}

void PhysicsEngine::objectUpdatePhysics(const float& dt) {
	// React on Player
	// Check for on ground
	
}
