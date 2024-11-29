#pragma once
#include "Block.h"
class SolidBlock :
    public Block
{
public:
	SolidBlock();
	SolidBlock(sf::Vector2f position, sf::Vector2f size, std::string name);
	virtual ~SolidBlock();
	//void initSpritesSheet();

	//Setters and Getters
	void update(const float& dt) override;
	void reactToObject(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

