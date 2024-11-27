#include "Headers/Block.h"

void Block::initSpritesSheet()
{
	spritesSheet["ground_1_1"] = sf::IntRect(1, 1, 16, 16);
	spritesSheet["underground_1_1"] = sf::IntRect(1, 18, 16, 16);

	spritesSheet["ground_1_2"] = sf::IntRect(18, 1, 16, 16);
	spritesSheet["underground_1_2"] = sf::IntRect(18, 18, 16, 16);

	spritesSheet["ground_1_3"] = sf::IntRect(35, 1, 50, 16);
	spritesSheet["underground_1_3"] = sf::IntRect(35, 18, 50, 33);

	spritesSheet["brick_1"] = sf::IntRect(1, 86, 16, 101);

	spritesSheet["coin_block_1"] = sf::IntRect(1, 52, 16, 67);
	spritesSheet["coin_block_2"] = sf::IntRect(18, 52, 33, 67);
	spritesSheet["coin_block_3"] = sf::IntRect(35, 52, 50, 67);
}

Block::Block()
{

}

Block::~Block()
{
}

Block::Block(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicEngine, std::string name)
	: GameObject(position, size, physicEngine)
{	
	initSpritesSheet();
	this->name = name;
	entityTexture.loadFromFile("Source/Resources/texture/Tileset.png");
	hitbox.setSize(size);
	//hitbox.setOrigin(size.x / 2, size.y / 2);
	hitbox.setPosition(sf::Vector2f(position.x, position.y));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);
	//hitbox.setOrigin(size.x / 2, size.y / 2);
}