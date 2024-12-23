#include "Headers/Mushroom.h"
#include "Headers/GameEventMediator.h"

Mushroom::Mushroom(sf::Vector2f position, sf::Vector2f size, std::string name, int type)
	: PowerUpObject(position, size, name)
{
	//The mushroom has a different file texture
	this->type = type;
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet[name + "_" + std::to_string(type)]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
}

Mushroom::~Mushroom()
{
}

void Mushroom::setFloatSpeed(float speed)
{
	floatSpeed = speed;
}

void Mushroom::update(const float& dt)
{
	floatTimer += dt;
	entitySprite.move(0, -floatSpeed * dt);

	// Reset position if it goes too high
	if (floatTimer >= 0.45f) {
		entitySprite.setPosition(entitySprite.getPosition().x, position.y);
	}
}

void Mushroom::reactToCollison()
{
	eventMediator->playMushroomSound();
	//Depend on the type of mushroom, we will spawn different things
	switch (type)
	{
	case 1:
		// Healing mushroom
		eventMediator->addPlayerHealth(1);
		break;
	case 2:
		//Grow big mushroom
		eventMediator->setPlayerBig(true);
		break;
	case 3:
		// 2 Healing mushroom
		eventMediator->addPlayerHealth(2);
		break;
	}
	//Delete this block
	eventMediator->deletePowerUp(this);
}

