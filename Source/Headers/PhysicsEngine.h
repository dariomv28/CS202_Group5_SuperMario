#pragma once
#include "stdafx.h"	

class PlayerManager;
class LivingEntity;
class Enemy;
class Block;
class GameObject;

class PhysicsEngine 
{
private:
	const float PIXELS_PER_METER = 16.0f;

	std::vector<Block*> blocks;
	std::vector<Enemy*> enemies;
	PlayerManager* player;
	sf::Vector2f gravity;
	sf::Vector2f friction;
	//void updateReact(LivingEntity* entity, const float& dt);
	void applyGravity(LivingEntity* obj, const float& dt);
	void applyFriction(LivingEntity* obj, const float& dt);
public:
	PhysicsEngine();
	bool checkCollision(GameObject* obj1, GameObject* obj2);
	bool checkCollideDown(GameObject* obj1, GameObject* obj2);
	bool checkCollideUp(GameObject* obj1, GameObject* obj2);
	bool checkCollideLeft(GameObject* obj1, GameObject* obj2);
	bool checkCollideRight(GameObject* obj1, GameObject* obj2);

	void addBlock(Block* obj);
	void addPlayer(PlayerManager* obj);
	//void updateMovement(LivingEntity* entity, const float& dt);
	//void playerUpdatePhysics(const float& dt);
	//void objectUpdatePhysics(const float& dt);
	void resolveCollision(LivingEntity* obj);
	void applyExternalForces(LivingEntity* entity, const float& dt);
};

