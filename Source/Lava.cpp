#include "Headers/Lava.h"

Lava::Lava(sf::Vector2f position, sf::Vector2f size, std::string name) :
    PowerUpObject(position, size, name)
{
    entityTexture.loadFromFile("Source/Resources/texture/tileset.png");
    entitySprite.setTexture(entityTexture);
    initSpritesSheet();
    entitySprite.setTextureRect(spritesSheet["lava_1"]);
    entitySprite.setPosition(position);
    entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width,
        size.y / entitySprite.getGlobalBounds().height);

    // Initialize animation variables
    currentFrame = 1;
    animationTimer = 0.f;
    animationSpeed = 0.12f; // Adjust this value to make animation faster or slower
    isAnimatingForward = true;
}

Lava::~Lava()
{
}

void Lava::initSpritesSheet() {
    spritesSheet = {
        {"lava_1", sf::IntRect(273, 154, 16, 16)},
        {"lava_2", sf::IntRect(290, 154, 16, 16)},
        {"lava_3", sf::IntRect(307, 154, 16, 16)},
        {"lava_4", sf::IntRect(324, 154, 16, 16)},
        {"lava_5", sf::IntRect(273, 171, 16, 16)},
        {"lava_6", sf::IntRect(290, 171, 16, 16)},
        {"lava_7", sf::IntRect(307, 171, 16, 16)},
        {"lava_8", sf::IntRect(324, 171, 16, 16)},
    };
}

void Lava::update(const float& dt) {
    // Update animation timer
    animationTimer += dt;

    // Check if it's time to update the frame
    if (animationTimer >= animationSpeed) {
        animationTimer = 0.f;

        if (isAnimatingForward) {
            currentFrame++;
            if (currentFrame > 8) {
                currentFrame = 7;
                isAnimatingForward = false;
            }
        }
        else {
            currentFrame--;
            if (currentFrame < 1) {
                currentFrame = 2;
                isAnimatingForward = true;
            }
        }

        std::string frameName = "lava_" + std::to_string(currentFrame);
        entitySprite.setTextureRect(spritesSheet[frameName]);
    }
}

void Lava::reactToCollison() {
    // Kill or damage the player
    eventMediator->decreasePlayerHealth();
}

void Lava::render(sf::RenderTarget* target) {
    target->draw(entitySprite);
}