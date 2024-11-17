#pragma once
#include "stdafx.h"

class PhysicsEngine;

class GameObject
{
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Sprite entitySprite;
	sf::Texture entityTexture;
	PhysicsEngine* physicsEngine;
	sf::RectangleShape hitbox;
public:
	GameObject();
	GameObject(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicEngine);
	virtual ~GameObject() {};
	sf::Vector2f getPosition();

	//Check Collisions in 4 sides of the object
	bool checkCollisionUp(GameObject& obj);
	bool checkCollisionDown(GameObject& obj);
	bool checkCollisionLeft(GameObject& obj);
	bool checkCollisionRight(GameObject& obj);

	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	virtual void setPosition(float x, float y);
	virtual void setPosition(const sf::Vector2f& pos);
};

	