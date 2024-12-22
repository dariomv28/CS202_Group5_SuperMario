#include "Headers/WinFlag.h"


WinFlag::WinFlag()
{
}

WinFlag::WinFlag(sf::Vector2f position, sf::Vector2f size, std::string name) :
	Block(position, size, name)
{
	initSpritesSheet();
}

WinFlag::~WinFlag()
{
}

void WinFlag::initSpritesSheet() {
	
}

void WinFlag::update(const float& dt) {
}

void WinFlag::reactToCollison(int collidedSide) {
}

void WinFlag::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
}