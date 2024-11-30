#include "Headers/Coin.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

Coin::Coin(sf::Vector2f position, sf::Vector2f size, std::string name)
	: Block(position, size, name)
{
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["coin_1"]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);

}

void Coin::update(const float& dt)
{
	//Update the animation
}

void Coin::reactToCollison(int collidedSide)
{
	//Increase coin or score

	//Delete this block

}

void Coin::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	target->draw(hitbox);
}


