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

	spritesSheet["gray_ground_left"] = sf::IntRect(290, 18, 16, 16);
	spritesSheet["gray_ground_mid"] = sf::IntRect(307, 18, 16, 16);
	spritesSheet["gray_ground_right"] = sf::IntRect(324, 18, 16, 16);
	spritesSheet["gray_underground_left"] = sf::IntRect(290, 35, 16, 16);
	spritesSheet["gray_underground_mid"] = sf::IntRect(307, 35, 16, 16);
	spritesSheet["gray_underground_right"] = sf::IntRect(324, 35, 16, 16);

	spritesSheet["gray_block1"] = sf::IntRect(393, 52, 16, 16);
	spritesSheet["gray_block2"] = sf::IntRect(392, 69, 16, 16);

	//Walls
	spritesSheet["basic_wall"] = spritesSheet["snow_wall"] = sf::IntRect(1, 155, 16, 16);
	spritesSheet["gray_wall"] = sf::IntRect(35, 155, 16, 16);


	//Bricks
	spritesSheet["basic_brick"] = spritesSheet["snow_brick"] = sf::IntRect(1, 86, 16, 16);
	spritesSheet["gray_brick"] = sf::IntRect(69, 86, 16, 16);


	//Coins Blocks
	spritesSheet["empty_question_block"] = sf::IntRect(1, 69, 16, 16);
	spritesSheet["question_block_1"] = sf::IntRect(1, 52, 16, 16);
	spritesSheet["question_block_2"] = sf::IntRect(18, 52, 16, 16);
	spritesSheet["question_block_3"] = sf::IntRect(35, 52, 16, 16);

	//Pipe
	spritesSheet["basic_pipe_bottom_left"] = sf::IntRect(103, 69, 16,16);
	spritesSheet["baisc_pipe_bottom_right"] = sf::IntRect(120, 69, 16, 16);
	spritesSheet["baisc_pipe_top_left"] = sf::IntRect(103, 52, 16, 16);
	spritesSheet["basic_pipe_top_right"] = sf::IntRect(120, 52, 16, 16);
	
	spritesSheet["gray_pipe_bottom_left"] = sf::IntRect(188, 69, 16, 16);
	spritesSheet["gray_pipe_bottom_right"] = sf::IntRect(205, 69, 16, 16);
	spritesSheet["gray_pipe_top_left"] = sf::IntRect(188, 52, 16, 16);
	spritesSheet["gray_pipe_top_right"] = sf::IntRect(205, 52, 16, 16);

	
	//Trampoline

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