#pragma once
#include "GameObject.h"

class Block :
    public GameObject
{
protected:
	std::string name;
	std::unordered_map<std::string, sf::IntRect> spritesSheet;
public:
	Block();
	Block(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicEngine, std::string name);
	virtual ~Block();
	void initSpritesSheet();

	//Setters and Getters
	void update(const float& dt) = 0;
	void render(sf::RenderTarget* target) = 0;
};

