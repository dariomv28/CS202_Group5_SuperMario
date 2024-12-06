#pragma once
#include "stdafx.h"

class PlayerManager;
class LivingEntity;
class Enemy;
class Block;
class GameObject;
class PhysicsEngine;
class LevelGUI;

class GameEventMediator
{
private:
	//Pointers to the original objects
	PhysicsEngine* physicsEngine;
	PlayerManager* player;
	std::vector<Block*>* blocks;
	std::vector<Enemy*>* enemies;
	LevelGUI* levelGUI;
public:
	// Initialization function
	GameEventMediator();
	~GameEventMediator();
	void addPlayer(PlayerManager* player);
	void addBlock(std::vector<Block*>& blocks);
	void addEnemy(std::vector<Enemy*>& enemies);
	void addPhysicsEngine(PhysicsEngine* physicsEngine);
	void addLevelGUI(LevelGUI* levelGUI);

	// Physics Engine functions
	void applyExternalForcesToEntities(const float& dt);
	void resolveCollision(const float& dt);
	
	// Update functions
	void updateInput(const float& dt);
	void updateMovements(const float& dt);
	void updateAnimations(const float& dt);
	void updateEvents(const float& dt);
	void updateLevelGUI(const sf::View& view);

	// Game Event functions
	void increaseCoins(int numCoins);
	void increaseScore(int numScore);
	void updateHealth(); // For LevelGUI
	void defeatPlayer();
	void deleteEnemy(Enemy* enemy);
	void deleteBlock(Block* block);
};

