#include "Headers/Coin.h"
#include "Headers/GameEventMediator.h"

Coin::Coin()
{
}

Coin::~Coin()
{
}

Coin::Coin(sf::Vector2f position, sf::Vector2f size, std::string name)
	: PowerUpObject(position, size, name)
{
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["coin_1"]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);

}

void Coin::update(const float& dt)
{
	//Update the animation
	updateAnimation(dt);
}

void Coin::updateAnimation(const float& dt)
{
	coinAnimationTimer += dt;
	if (coinAnimationTimer >= 0.1f) {
		entitySprite.setTextureRect(spritesSheet["coin_" + std::to_string(coinAnimationCurrentFrame + 1)]);
		coinAnimationCurrentFrame = (coinAnimationCurrentFrame + 1) % 3;
		coinAnimationTimer = 0.0f;
	}
}

void Coin::reactToCollison()
{
	//Increase coin or score
	eventMediator->increaseCoins(1);
	eventMediator->playCoinSound();

	//Delete this block
	eventMediator->deletePowerUp(this);
}

void Coin::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
}


