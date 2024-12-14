#pragma once
#include "GameObject.h"
#include "PlayerManager.h"
#include "Enemy.h"


class Block :
	public GameObject
{
protected:
	std::string name;
	std::unordered_map<std::string, sf::IntRect> spritesSheet;

	bool exist;

public:

	Block();
	Block(sf::Vector2f position, sf::Vector2f size, std::string name);
	virtual ~Block();
	virtual void initSpritesSheet() = 0;

	//Setters and Getters
	virtual void update(const float& dt) = 0;
	virtual void reactToCollison(int collidedSide) = 0;
	virtual void render(sf::RenderTarget* target) = 0;

	virtual void initAnimations();
	virtual void updateAnimation(const float& dt);

	virtual void setExist(bool exist);
	virtual bool getExist();

	AnimationComponent* animationComponent;
};

