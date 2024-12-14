#include "Headers/GameEventMediator.h"
#include "Headers/PlayerManager.h"
#include "Headers/Block.h"
#include "Headers/Enemy.h"
#include "Headers/PhysicsEngine.h"
#include "Headers/PowerUpObject.h"
#include "Headers/LevelGUI.h"

GameEventMediator::GameEventMediator() {
}

GameEventMediator::~GameEventMediator() {
}

void GameEventMediator::addPlayer(PlayerManager* player) {
	this->player = player;
	player->setEventMediator(this);
}

void GameEventMediator::addBlock(std::vector<Block*>& blocks) {
	this->blocks = &blocks;
	for (auto& block : blocks) {
		block->setEventMediator(this);
	}
}

void GameEventMediator::addEnemy(std::vector<Enemy*>& enemies) {
	this->enemies = &enemies;
	for (auto& enemy : enemies) {
		enemy->setEventMediator(this);
	}
}

void GameEventMediator::addPhysicsEngine(PhysicsEngine* physicsEngine) {
	this->physicsEngine = physicsEngine;
}

void GameEventMediator::addLevelGUI(LevelGUI* levelGUI) {
	this->levelGUI = levelGUI;
}

void GameEventMediator::addPowerUp(std::vector<PowerUpObject*>& PowerUps) {
	this->PowerUps = &PowerUps;
	for (auto& PowerUp : PowerUps) {
		PowerUp->setEventMediator(this);
	}
}

//void GameEventMediator::addAudioSystem(AudioSystem* audio) {
//	this->audio = audio;
//}


void GameEventMediator::applyExternalForce(LivingEntity* entity, const float& dt) {
	// Apply gravity to all entities
	physicsEngine->applyExternalForces(entity, dt);
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
	// Update events of the objects by themselves
	player->update(dt);
	for (auto& enemy : *enemies) {
		enemy->update(dt);
	}

	for (auto& block : *blocks) {
		block->update(dt);
	}

	for (auto& PowerUp : *PowerUps) {
		PowerUp->update(dt);
	}
	
	// Update evetns from collisions
	resolveCollision(dt);
}

void GameEventMediator::updateLevelGUI(const sf::View& view) {
	levelGUI->update(view);
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

void GameEventMediator::pushPlayerLeft() {
	player->setVelocity(sf::Vector2f(-10.0f, player->getVelocity().y));
}

void GameEventMediator::pushPlayerRight() {
	player->setVelocity(sf::Vector2f(10.0f, player->getVelocity().y));
}

void GameEventMediator::spawnPowerUp(PowerUpObject* PowerUp) {
	this->PowerUps->push_back(PowerUp);
	PowerUp->setEventMediator(this);
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