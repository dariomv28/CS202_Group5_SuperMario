#pragma once
#include "GameObject.h"

class PhysicsEngine 
{
private:
	std::list<GameObject> objects;
	float gravity;
	sf::Vector2f horizontalUserForce;
	sf::Vector2f verticalUserForce;


public:
	PhysicsEngine();

};

