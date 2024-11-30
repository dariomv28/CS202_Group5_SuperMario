#include "Headers/Brick.h"


Brick::Brick()
{
}

Brick::Brick(sf::Vector2f position, sf::Vector2f size, std::string name, int hiddenObject)
	: Block(position, size, name)
{
	this->hiddenObject = hiddenObject;
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet[name]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
}

Brick::~Brick()
{
}

void Brick::update(const float& dt)
{
}

void Brick::reactToCollison(int collidedSide)
{
	if (collidedSide == Collide_Bottom) {
		if (hiddenObject == 0) return;
		//Depend on the Hidden object, we will spawn different things
		switch (hiddenObject)
		{
		default:
			break;
		}
		hiddenObject = 0;
	}
}

void Brick::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	target->draw(hitbox);
}
