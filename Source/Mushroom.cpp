#include "Headers/Mushroom.h"
#include "Headers/GameEventMediator.h"

Mushroom::Mushroom(sf::Vector2f position, sf::Vector2f size, std::string name, int type)
	: PowerUpObject(position, size, name)
{
	//The mushroom has a different file texture
	this->type = type;
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet[name + std::to_string(type)]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
}

Mushroom::~Mushroom()
{
}

void Mushroom::update(const float& dt)
{
}

void Mushroom::reactToCollison()
{
	//Depend on the type of mushroom, we will spawn different things
	switch (type)
	{
	case 1:
		// Grow big mushroom
		eventMediator->setPlayerBig(true);
		break;
	case 2:
		//Fire mushroom
		break;
	}
	//Delete this block
	eventMediator->deletePowerUp(this);
}

