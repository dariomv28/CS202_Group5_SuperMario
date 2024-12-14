#include "Headers/Block.h"

void Block::initSpritesSheet()
{
	//Grounds
	spritesSheet["basic_ground_left"] = sf::IntRect(1, 1, 16, 16);
	spritesSheet["basic_ground_mid"] = sf::IntRect(18, 1, 16, 16);
	spritesSheet["basic_ground_right"] = sf::IntRect(35, 1, 16, 16);
	spritesSheet["basic_underground_left"] = sf::IntRect(1, 18, 16, 16);
	spritesSheet["basic_underground_mid"] = sf::IntRect(18, 18, 16, 16);
	spritesSheet["basic_underground_right"] = sf::IntRect(35, 18, 16, 16);

	spritesSheet["snow_ground_left"] = sf::IntRect(137, 1, 16, 16);
	spritesSheet["snow_ground_mid"] = sf::IntRect(154, 1, 16, 16);
	spritesSheet["snow_ground_right"] = sf::IntRect(171, 1, 16, 16);
	spritesSheet["snow_underground_left"] = sf::IntRect(137, 18, 16, 16);
	spritesSheet["snow_underground_mid"] = sf::IntRect(154, 18, 16, 16);
	spritesSheet["snow_underground_right"] = sf::IntRect(171, 18, 16, 16);

	//Walls
	spritesSheet["wall_1"] = sf::IntRect(1, 155, 16, 16);

	//Bricks
	spritesSheet["brick_1"] = sf::IntRect(1, 86, 16, 16);

	//Coins Blocks
	spritesSheet["empty_question_block"] = sf::IntRect(1, 69, 16, 16);
	spritesSheet["question_block_1"] = sf::IntRect(1, 52, 16, 16);
	spritesSheet["question_block_2"] = sf::IntRect(18, 52, 16, 16);
	spritesSheet["question_block_3"] = sf::IntRect(35, 52, 16, 16);

	//Pipe
	spritesSheet["pipe_bottom_left"] = sf::IntRect(103, 69, 16,16);
	spritesSheet["pipe_bottom_right"] = sf::IntRect(120, 69, 16, 16);
	spritesSheet["pipe_top_left"] = sf::IntRect(103, 52, 16, 16);
	spritesSheet["pipe_top_right"] = sf::IntRect(120, 52, 16, 16);

	//Coin
	spritesSheet["coin_1"] = sf::IntRect(52, 52, 16, 16);
	spritesSheet["coin_2"] = sf::IntRect(69, 52, 16, 16);
	spritesSheet["coin_3"] = sf::IntRect(86, 52, 16, 16);

}

Block::Block()
{

}

Block::~Block()
{
}

Block::Block(sf::Vector2f position, sf::Vector2f size, std::string name)
	: GameObject(position, size)
{	
	initSpritesSheet();
	this->name = name;
	this->exist = true;
	entityTexture.loadFromFile("Source/Resources/texture/Tileset.png");
	hitbox.setSize(size);
	//hitbox.setOrigin(size.x / 2, size.y / 2);
	hitbox.setPosition(sf::Vector2f(position.x, position.y));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1);

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