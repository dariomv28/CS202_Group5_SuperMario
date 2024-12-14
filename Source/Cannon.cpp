#include "Headers/Cannon.h"

Cannon::Cannon() : Block() {
}

Cannon::Cannon(sf::Vector2f position, sf::Vector2f size, std::string name)
	: Block(position, size, name)
{
	initSpritesSheet();
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["cannon"]);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	entitySprite.setPosition(position);
}

Cannon::~Cannon() {
}

void Cannon::initSpritesSheet() {
	spritesSheet = {
		{"cannon", sf::IntRect(69, 137, 16, 16)}
	};
}

void Cannon::update(const float& dt) {

}

void Cannon::reactToCollison(int collidedSide) {
}

void Cannon::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
}

