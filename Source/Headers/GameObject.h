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
public:
	sf::RectangleShape hitbox;

	GameObject();
	GameObject(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicEngine);
	virtual ~GameObject() {};
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::Vector2f getCenter() const;

    // Helper function to check if the line intersects the top of the object
   
	//Check Collisions in 4 sides of the object
	bool checkCollisionUp(GameObject* obj);
	bool checkCollisionDown(GameObject* obj);
	bool checkCollisionLeft(GameObject* obj);
	bool checkCollisionRight(GameObject* obj);

	void setSize(const sf::Vector2f& newSize);

	virtual void update(const float& dt) = 0;
	//virtual void reactToObject(PlayerManager* player, std::vector<Block*> blocks, std::vector<Enemy> enemies) = 0;

	virtual void render(sf::RenderTarget* target) = 0;

	virtual void setPosition(float x, float y);
	virtual void setPosition(const sf::Vector2f& pos);
};

	