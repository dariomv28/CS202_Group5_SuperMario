#include "Headers/CoinBlock.h"
#include "Headers/GameEventMediator.h"

CoinBlock::CoinBlock()
{
	this->numCoins = 0;
}

CoinBlock::CoinBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int numCoins) :
	Block(position, size, name) 
{
	this->numCoins = numCoins;
	entitySprite.setTexture(entityTexture);
	
	entitySprite.setTextureRect(spritesSheet["question_block_1"]); 
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
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
	// std::cout << "COINBLOCK COLLIDED " << collidedSide << std::endl;
	if (collidedSide == Collide_Bottom) {
		if (numCoins == 0) return;
		this->eventMediator->increaseCoins(1);
		this->eventMediator->increaseScore(100);

		//std::cerr << "Coin collected\n";
		
		//Decrease the number of coins in the block
		numCoins--;
		if (numCoins == 0) {
			entitySprite.setTextureRect(spritesSheet["empty_question_block"]);
		}
	}
}

void CoinBlock::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	target->draw(hitbox);
}


