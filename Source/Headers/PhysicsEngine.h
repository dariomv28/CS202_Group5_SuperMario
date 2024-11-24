#pragma once
#include "stdafx.h"	

class GameObject;
class PlayerManager;
class LivingEntity;
class Enemy;

class PhysicsEngine 
{
private:
	const float PIXELS_PER_METER = 16.0f;

	std::vector<GameObject*> objects;
	std::vector<Enemy*> enemies;
	PlayerManager* player;
	sf::Vector2f gravity;
	sf::Vector2f friction;

	void updateMovement(LivingEntity* entity, const float& dt);
	//void updateReact(LivingEntity* entity, const float& dt);
	void applyGravity(LivingEntity* obj, const float& dt);
	void applyFriction(LivingEntity* obj, const float& dt);
	void resolveCollision(LivingEntity* obj);
public:
	PhysicsEngine();
	void addObject(GameObject* obj);
	void addPlayer(PlayerManager* obj);
	void playerUpdatePhysics(const float& dt);
	void objectUpdatePhysics(const float& dt);
	//bool checkCollision(GameObject& obj1, GameObject& obj2);
	//void resolveCollision(GameObject& obj1, GameObject& obj2);
	//void updatePhysics();
	//void applyUserInput(GameObject& obj);
};

