#include "Headers/CoinBlock.h"

CoinBlock::CoinBlock()
{
	this->numCoins = 0;
}

CoinBlock::CoinBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int numCoins) :
	SolidBlock(position, size, name)
{
	this->numCoins = numCoins;
}

CoinBlock::~CoinBlock()
{
}

void CoinBlock::update(const float& dt)
{
}

void CoinBlock::reactToObject(int collidedSide)
{
}

void CoinBlock::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	target->draw(hitbox);
}


