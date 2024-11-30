#pragma once
#include "Block.h"

//Name = "coin"
class Coin :
    public Block
{
public:
    Coin();
	Coin(sf::Vector2f position, sf::Vector2f size, std::string name);
	virtual ~Coin();
	void update(const float& dt) override;
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

