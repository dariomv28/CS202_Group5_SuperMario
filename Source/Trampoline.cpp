#include "Headers/Trampoline.h"

Trampoline::Trampoline() : Block() {
}

Trampoline::Trampoline(sf::Vector2f position, sf::Vector2f size, std::string name)
	: Block(position, size, name)
{
	initSpritesSheet();
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["trampoline_1"]);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	entitySprite.setPosition(position);
}

Trampoline::~Trampoline() {
}

void Trampoline::initSpritesSheet() {
	spritesSheet = {
		{"trampoline_1", sf::IntRect(35, 240, 16, 16)}

	};
}

void Trampoline::update(const float& dt) {

}

void Trampoline::reactToCollison(int collidedSide) {
}

void Trampoline::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
}

