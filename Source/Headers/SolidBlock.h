#pragma once
#include "Block.h"

// This class contains solid blocks (grounds, walls, etc.). See Block.h to get the names of the blocks
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
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

