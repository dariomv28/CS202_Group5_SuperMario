#pragma once
#include "stdafx.h"

class GameEventMediator;

class GameObject
{
protected:
	sf::Vector2f position;
	sf::Vector2f size;
	sf::Sprite entitySprite;
	sf::Texture entityTexture;
	GameEventMediator* eventMediator;
public:
	sf::RectangleShape hitbox;

	GameObject();
	GameObject(sf::Vector2f position, sf::Vector2f size);
	virtual ~GameObject() {};

	//Setters and Getters
	sf::Vector2f getPosition();
	sf::Vector2f getSize();
	sf::Vector2f getCenter() const;
	void setSize(const sf::Vector2f& newSize);
	virtual void setPosition(float x, float y);
	virtual void setPosition(const sf::Vector2f& pos);
	void setEventMediator(GameEventMediator* mediator);

	virtual void update(const float& dt) = 0;
	//virtual void reactToObject(PlayerManager* player, std::vector<Block*> blocks, std::vector<Enemy> enemies) = 0;

	virtual void render(sf::RenderTarget* target) = 0;
};

	