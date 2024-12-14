#include "Headers/SolidBlock.h"

SolidBlock::SolidBlock() : Block() {
}

SolidBlock::SolidBlock(sf::Vector2f position, sf::Vector2f size, std::string name)
	: Block(position, size, name)
{
	initSpritesSheet();

	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet[name]);
	
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	//entitySprite.setPosition(sf::Vector2f(0, 0));
	//entitySprite.setOrigin(size.x / 2, size.y / 2);
	entitySprite.setPosition(sf::Vector2f(position.x , position.y ));
	//entitySprite.setOrigin(size.x / 2, size.y / 2);

}


SolidBlock::~SolidBlock() {
}

void SolidBlock::initSpritesSheet() {
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

	//Lava
	spritesSheet["lava_bottom"] = sf::IntRect(273, 171, 16, 16);

	//Cannon
	spritesSheet["cannon_mid"] = sf::IntRect(69, 154, 16, 16);	
	spritesSheet["cannon_bottom"] = sf::IntRect(69, 171, 16, 16);

}

void SolidBlock::update(const float& dt) {

}

void SolidBlock::reactToCollison(int collidedSide) {

}

void SolidBlock::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
	target->draw(hitbox);
}