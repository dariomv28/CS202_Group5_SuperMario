#pragma once
#include "stdafx.h"

class PlayerManager;
class LivingEntity;
class Enemy;
class Block;
class GameObject;
class PhysicsEngine;

class GameEventMediator
{
private:
	PhysicsEngine* physicsEngine;
	PlayerManager* player;
	std::vector<Block*> blocks;
	std::vector<Enemy*> enemies;
	//std::vector<LivingEntity*> livingEntities;
public:
	// Initialization function
	GameEventMediator();
	~GameEventMediator();
	void addPlayer(PlayerManager* player);
	void addBlock(Block* block);
	void addEnemy(Enemy* enemy);
	void addPhysicsEngine(PhysicsEngine* physicsEngine);

	// Physics Engine functions
	void applyExternalForcesToEntities(const float& dt);
	void resolveCollision(const float& dt);
	
	// Update functions
	void updateInput(const float& dt);
	void updateMovements(const float& dt);
	void updateAnimations(const float& dt);

	// Game Event functions
};

