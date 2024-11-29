#include "Headers/CoinBlock.h"

CoinBlock::CoinBlock()
{
	this->numCoins = 0;
}

CoinBlock::CoinBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int numCoins) :
	Block(position, size, name) 
{
	this->numCoins = numCoins;
	entitySprite.setTexture(entityTexture);
	// Since the block has animation, we need to set the first frame of the animation by adding _1 to the name
	entitySprite.setTextureRect(spritesSheet[name + "_1"]); 
}

CoinBlock::~CoinBlock()
{
}

void CoinBlock::update(const float& dt)
{
	//Update the animation of the block
}

void CoinBlock::reactToCollison(int collidedSide)
{
	// Update the bouncing effect latter (Or have another ancestor class to handle the bouncing effect for multiple blocks)
	if (collidedSide == Collide_Bottom) {
		if (numCoins == 0) return;
		//Increase the coins of player
		
		//Decrease the number of coins in the block
		numCoins--;
		if (numCoins == 0) {
			entitySprite.setTextureRect(spritesSheet["empty_" + name]);
		}
	}
}

void CoinBlock::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	target->draw(hitbox);
}


