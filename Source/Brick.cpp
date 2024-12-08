#include "Headers/Brick.h"
#include "Headers/GameEventMediator.h"

Brick::Brick()
{
}

Brick::Brick(sf::Vector2f position, sf::Vector2f size, std::string name, bool breakable)
	: Block(position, size, name)
{
	this->breakable = breakable;
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
		if (breakable) {
			eventMediator->increaseScore(50);
			eventMediator->deleteBlock(this);
		}
	}
}

void Brick::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	target->draw(hitbox);
}
