#include "Headers/Block.h"

Block::Block()
{

}

Block::~Block()
{
}

Block::Block(sf::Vector2f position, sf::Vector2f size, std::string name)
	: GameObject(position, size)
{	
	this->name = name;
	this->exist = true;
	entityTexture.loadFromFile("Source/Resources/texture/Tileset.png");
	hitbox.setSize(size);
	//hitbox.setOrigin(size.x / 2, size.y / 2);
	hitbox.setPosition(sf::Vector2f(position.x, position.y));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1.f);

	//hitbox.setOrigin(size.x / 2, size.y / 2);
}


void Block::initAnimations() {};

void Block::updateAnimation(const float& dt) {};

bool Block::getExist() {
	return exist;
}

void Block::setExist(bool exist) {
	this->exist = exist;
}