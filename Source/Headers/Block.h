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
public:
	Block();
	Block(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicEngine, std::string name);
	virtual ~Block();
	void initSpritesSheet();

	//Setters and Getters
	virtual void update(const float& dt) = 0;
	virtual void reactToObject(PlayerManager* player, std::vector<Block*> blocks, std::vector<Enemy> enemies) = 0;
	virtual void render(sf::RenderTarget* target) = 0;
};

