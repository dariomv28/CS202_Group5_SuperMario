#pragma once
#include "Block.h"

//Name = "mushroom_block" 
class MushroomBlock :
    public Block
{
private:
    int type;

	bool isBlockBouncing = false;
	float blockBounceTimer = 0.0f;
	sf::Vector2f originalBlockPosition;
	float bounceDistance = 5.0f;

	float mushroomBlockAnimationTimer = 0.0f;
	int mushroomBlockAnimationCurrentFrame = 0;
public:
    MushroomBlock();
	MushroomBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int type);
	virtual ~MushroomBlock();

	void initSpritesSheet();
	void update(const float& dt) override;
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;

	void updateAnimation(const float& dt) override;
};

