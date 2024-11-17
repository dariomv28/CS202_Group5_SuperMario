#include "Headers/PhysicsEngine.h"
#include "Headers/PlayerManager.h"
#include "Headers/GameObject.h"
#include "Headers/LivingEntity.h"
#include "Headers/Enemy.h"

PhysicsEngine::PhysicsEngine() {
	gravity = sf::Vector2f(0, 10);
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
}

void PhysicsEngine::resolveCollision(LivingEntity* entity) {
	// Resolve on the ground
	entity->setOnGround(false);
	if (entity->getVelocity().y > 0) {
		for (auto obj : objects) {
			if (entity->checkCollisionDown(*obj)) {
				entity->setOnGround(true);
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
	if (!entity->getOnGround()) {
		applyGravity(entity, dt);
	}
}

void PhysicsEngine::playerUpdatePhysics(const float& dt) {
	updateMovement(player, dt);
}

void PhysicsEngine::objectUpdatePhysics(const float& dt) {
	// React on Player
	// Check for on ground
	
}
