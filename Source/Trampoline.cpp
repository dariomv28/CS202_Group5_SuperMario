#include "Headers/Trampoline.h"

Trampoline::Trampoline() : Block() {
	initVariables();
}

Trampoline::Trampoline(sf::Vector2f position, sf::Vector2f size, std::string name)
    : Block(position, size, name)
{
    initVariables();
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
    if (isCompressed) {
        if (shouldBounce) {
            // Compression animation
            currentFrame++;
            if (currentFrame > 3) {
                shouldBounce = false;
            }
        }
        else {
            // Decompression animation
            currentFrame--;
            if (currentFrame < 1) {
                currentFrame = 1;
                isCompressed = false;
            }
        }
        // Update sprite texture
        std::string frameName = "trampoline_" + std::to_string(currentFrame);
        entitySprite.setTextureRect(spritesSheet[frameName]);
    }
}

void Trampoline::reactToCollison(int collidedSide) {
    if (collidedSide == Collide_Top) {
        eventMediator->pushPlayerUpExtra();
		startBounceAnimation();
    }
}   

void Trampoline::initVariables() {
    isCompressed = false;
    animationTimer = 0.0f;
    currentFrame = 1;
    shouldBounce = false;
}

void Trampoline::startBounceAnimation() {
    isCompressed = true;
    shouldBounce = true;
    currentFrame = 1;
    animationTimer = 0.0f;
}

void Trampoline::render(sf::RenderTarget* target) {
    target->draw(entitySprite);
}