#include "Headers/Mushroom.h"

Mushroom::Mushroom(sf::Vector2f position, sf::Vector2f size, std::string name, int type)
	: Block(position, size, name)
{
	//The mushroom has a different file texture
	entityTexture.loadFromFile("Source/Resources/texture/Items_Blocks.png");
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

void Mushroom::reactToCollison(int collidedSide)
{
	//Depend on the type of mushroom, we will spawn different things
	switch (type)
	{
	default:
		break;
	}
}

void Mushroom::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	target->draw(hitbox);
}


