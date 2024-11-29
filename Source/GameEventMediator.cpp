#include "Headers/GameEventMediator.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/Enemy.h"
#include "Headers/PhysicsEngine.h"

GameEventMediator::GameEventMediator() {
}

GameEventMediator::~GameEventMediator() {
}

void GameEventMediator::addPlayer(PlayerManager* player) {
	this->player = player;
}

void GameEventMediator::addBlock(Block* block) {
	blocks.push_back(block);
}

void GameEventMediator::addEnemy(Enemy* enemy) {
	enemies.push_back(enemy);
}

void GameEventMediator::addPhysicsEngine(PhysicsEngine* physicsEngine) {
	this->physicsEngine = physicsEngine;
}

void GameEventMediator::updateMovements(const float& dt) {
	// Update velocity of all entities
	player->updateVelocity(dt);
	for (auto& enemy : enemies) {
		enemy->updateVelocity(dt);
	}
	//Apply external forces to all entities
	applyExternalForcesToEntities(dt);
	// Update position of all entities
	player->move(dt);
	for (auto& enemy : enemies) {
		enemy->move(dt);
	}
}

void GameEventMediator::applyExternalForcesToEntities(const float& dt) {
	// Apply gravity to all entities
	for (auto& enemy : enemies) {
		physicsEngine->applyExternalForces(enemy, dt);
	}
	physicsEngine->applyExternalForces(player, dt);
}

void GameEventMediator::resolveCollision(const float& dt) {
	// Resolve collision between player and blocks
	physicsEngine->resolveCollisionPlayerBlock(player, blocks, dt);
	// Resolve collision between enemies and blocks
	physicsEngine->resolveCollisionEnemyBlock(enemies, blocks, dt);
	// Resolve collision between player and enemies
	physicsEngine->resolveCollisionPlayerEnemy(player, enemies, dt);
}

void GameEventMediator::updateInput(const float& dt) {
	player->handleInput(dt);

}

void GameEventMediator::updateAnimations(const float& dt) {
	player->updateAnimation(dt);
	for (auto& enemy : enemies) {
		enemy->updateAnimation(dt);
	}
}