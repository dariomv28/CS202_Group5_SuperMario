#pragma once
#include "stdafx.h"	
#include "GameEventMediator.h"


class PhysicsEngine 
{
private:
	const float PIXELS_PER_METER = 16.0f;

	GameEventMediator* eventMediator;
	sf::Vector2f gravity;
	sf::Vector2f friction;
	//void updateReact(LivingEntity* entity, const float& dt);
	void applyGravity(LivingEntity* obj, const float& dt);
	void applyFriction(LivingEntity* obj, const float& dt);
public:
	PhysicsEngine();

	//Setters and Getters
	void setEventMediator(GameEventMediator* mediator);

	//Colissions checking
	bool checkCollision(GameObject* obj1, GameObject* obj2);
	bool checkCollideDown(GameObject* obj1, GameObject* obj2);
	bool checkCollideUp(GameObject* obj1, GameObject* obj2);
	bool checkCollideLeft(GameObject* obj1, GameObject* obj2);
	bool checkCollideRight(GameObject* obj1, GameObject* obj2);

	//Physics functions
	void fixPosition(LivingEntity* entity, GameObject* obj, int collidedSide);
	void resolveCollisionPlayerBlock(PlayerManager* entity, std::vector<Block*>& blocks, const float& dt);
	void resolveCollisionPlayerEnemy(PlayerManager* entity, std::vector<Enemy*>& enemies, const float& dt);
	void resolveCollisionEnemyBlock(std::vector<Enemy*>& enemies, std::vector<Block*>& blocks, const float& dt);
	void applyExternalForces(LivingEntity* entity, const float& dt);
	void resolveCollisionEnemyEnemy(std::vector<Enemy*>& enemies, const float& dt);
};

