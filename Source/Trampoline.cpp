#include "Headers/Trampoline.h"

Trampoline::Trampoline() : Block() {
}

Trampoline::Trampoline(sf::Vector2f position, sf::Vector2f size, std::string name)
    : Block(position, size, name)
{
    initSpritesSheet();
    entitySprite.setTexture(entityTexture);
    entitySprite.setTextureRect(spritesSheet["trampoline_1"]);
    entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width,
        size.y / entitySprite.getGlobalBounds().height);
    entitySprite.setPosition(position);
}

Trampoline::~Trampoline() {
}

void Trampoline::initSpritesSheet() {
    spritesSheet = {
        {"trampoline_1", sf::IntRect(18, 232, 16, 24)},  // Normal state
        {"trampoline_2", sf::IntRect(35, 232, 16, 24)},  // Compressed state
        {"trampoline_3", sf::IntRect(35, 232, 16, 24)}   // Most compressed state
    };
}

void Trampoline::update(const float& dt) {
    updateAnimation(dt);
}

void Trampoline::updateAnimation(const float& dt) {
        
   
}

void Trampoline::reactToCollison(int collidedSide) {
    if (collidedSide == Collide_Top) {
        eventMediator->pushPlayerUpExtra();
		isCompressed = true;
    }
}   

void Trampoline::render(sf::RenderTarget* target) {
    target->draw(entitySprite);
}