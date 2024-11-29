#include "Headers/SolidBlock.h"

SolidBlock::SolidBlock() : Block() {
}

SolidBlock::SolidBlock(sf::Vector2f position, sf::Vector2f size, std::string name)
	: Block(position, size, name)
{
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

void SolidBlock::update(const float& dt) {

}

void SolidBlock::reactToCollison(int collidedSide) {

}

void SolidBlock::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
	target->draw(hitbox);
}