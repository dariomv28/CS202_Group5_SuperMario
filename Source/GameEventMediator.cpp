#include "Headers/GameEventMediator.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/Enemy.h"
#include "Headers/PhysicsEngine.h"
#include "Headers/LevelGUI.h"

GameEventMediator::GameEventMediator() {
}

GameEventMediator::~GameEventMediator() {
}

void GameEventMediator::addPlayer(PlayerManager* player) {
	this->player = player;
}

void GameEventMediator::addBlock(std::vector<Block*>& blocks) {
	this->blocks = &blocks;
}

void GameEventMediator::addEnemy(std::vector<Enemy*>& enemies) {
	this->enemies = &enemies;
}

void GameEventMediator::addPhysicsEngine(PhysicsEngine* physicsEngine) {
	this->physicsEngine = physicsEngine;
}

void GameEventMediator::addLevelGUI(LevelGUI* levelGUI) {
	this->levelGUI = levelGUI;
}

void GameEventMediator::addPowerUp(std::vector<PowerUpObject*>& PowerUps) {
	this->PowerUps = &PowerUps;
}

void GameEventMediator::updateMovements(const float& dt) {
	// Update velocity of all entities
	player->updateVelocity(dt);
	for (auto& enemy : *enemies) {
		enemy->updateVelocity(dt);
	}
	//Apply external forces to all entities
	applyExternalForcesToEntities(dt);
	// Update position of all entities
	player->move(dt);
	//std::cerr << player->getPosition().x << " " << player->getPosition().y << "\n";
	
	for (auto& enemy : *enemies) {
		enemy->move(dt);
	}
}

void GameEventMediator::applyExternalForcesToEntities(const float& dt) {
	// Apply gravity to all entities
	for (auto& enemy : *enemies) {
		physicsEngine->applyExternalForces(enemy, dt);
	}
	physicsEngine->applyExternalForces(player, dt);
}

void GameEventMediator::resolveCollision(const float& dt) {
	// Resolve collision between player and blocks
	physicsEngine->resolveCollisionPlayerBlock(player, *blocks, dt);
	// Resolve collision between enemies and blocks
	physicsEngine->resolveCollisionEnemyBlock(*enemies, *blocks, dt);
	// Resolve collision between enemies and enemies
	physicsEngine->resolveCollisionEnemyEnemy(*enemies, dt);
	// Resolve collision between player and enemies
	physicsEngine->resolveCollisionPlayerEnemy(player, *enemies, dt);
	// Resolve collision between player and powerups
	physicsEngine->resolveCollisionPlayerPowerUp(player, *PowerUps, dt);
	updateHealth();
}

void GameEventMediator::updateInput(const float& dt) {
	player->handleInput(dt);
}

void GameEventMediator::updateEvents(const float& dt) {
	// Update events from the map

	
	// Update evetns from collisions
	resolveCollision(dt);
}

void GameEventMediator::updateLevelGUI(const sf::View& view) {
	levelGUI->update(view);
}

void GameEventMediator::updateAnimations(const float& dt) {
	player->updateAnimation(dt);
	for (auto& enemy : *enemies) {
		enemy->updateAnimation(dt);
	}
}

void GameEventMediator::increaseCoins(int numCoins) {
	levelGUI->increaseCoins(numCoins);
}

void GameEventMediator::increaseScore(int numScore) {
	levelGUI->increaseScore(numScore);
}

void GameEventMediator::updateHealth() {
	levelGUI->updateHealth(player->getHealth()); // Just for testing
}

void GameEventMediator::setPlayerBig(bool big) {
	player->setBig(big);
}

void GameEventMediator::decreasePlayerHealth() {
	player->setHealth(player->getHealth() - 1);
}

void GameEventMediator::defeatPlayer() {
	//
}

void GameEventMediator::deleteEnemy(Enemy* enemy) {
	// Delete enemy from enemies
	for (auto it = enemies->begin(); it != enemies->end(); ++it) {
		if (*it == enemy) {
			enemies->erase(it);
			break;
		}
	}
}

void GameEventMediator::deleteBlock(Block* block) {
	// Delete block from blocks
	for (auto it = blocks->begin(); it != blocks->end(); ++it) {
		if (*it == block) {
			blocks->erase(it);
			break;
		}
	}
}

void GameEventMediator::deletePowerUp(PowerUpObject* PowerUp) {
	// Delete PowerUp from PowerUps
	for (auto it = PowerUps->begin(); it != PowerUps->end(); ++it) {
		if (*it == PowerUp) {
			PowerUps->erase(it);
			break;
		}
	}
}