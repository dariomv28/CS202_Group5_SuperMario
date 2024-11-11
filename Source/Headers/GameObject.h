#pragma once
#include "stdafx.h"
class GameObject
{
protected:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f size;
	sf::Vector2f netForce;
public:
	GameObject() {};
	GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f size);
	GameObject(const GameObject& other);
	virtual void move() = 0;
	bool checkCollision(const GameObject& other);
	sf::Vector2f getPosition();
	void setForce(sf::Vector2f force);
	void exertForceOnOther(GameObject& other, sf::Vector2f force);
};

