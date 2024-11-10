#pragma once
#include "stdafx.h"
class GameObject
{
protected:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f size;
public:
	GameObject() {};
	GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f size);
	GameObject(const GameObject& other);
	virtual void move() = 0;
	bool checkCollision(const GameObject& other);
	sf::Vector2f getPosition();

};

