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
	//Pointers to the original objects
	PhysicsEngine* physicsEngine;
	PlayerManager* player;
	std::vector<Block*>* blocks;
	std::vector<Enemy*>* enemies;
public:
	// Initialization function
	GameEventMediator();
	~GameEventMediator();
	void addPlayer(PlayerManager* player);
	void addBlock(std::vector<Block*>& blocks);
	void addEnemy(std::vector<Enemy*>& enemies);
	void addPhysicsEngine(PhysicsEngine* physicsEngine);

	// Physics Engine functions
	void applyExternalForcesToEntities(const float& dt);
	void resolveCollision(const float& dt);
	
	// Update functions
	void updateInput(const float& dt);
	void updateMovements(const float& dt, const sf::View& view);
	void updateAnimations(const float& dt);
	void updateEvents(const float& dt);

	// Game Event functions
};

