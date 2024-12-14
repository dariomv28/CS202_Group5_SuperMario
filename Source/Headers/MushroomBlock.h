#pragma once
#include "Block.h"

//Name = "mushroom_block" 
class MushroomBlock :
    public Block
{
private:
    int type;
public:
    MushroomBlock();
	MushroomBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int type);
	virtual ~MushroomBlock();

	void initSpritesSheet();
	void update(const float& dt) override;
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

