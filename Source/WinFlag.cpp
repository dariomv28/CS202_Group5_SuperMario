#include "Headers/WinFlag.h"

WinFlag::WinFlag(sf::Vector2f position, sf::Vector2f size, std::string name) :
    Block(position, size, name)
{
    animationState = FlagState::IDLE;
    isAnimating = false;
    flagPosition = position.y;
    animationTimer = 0.0f;

    // Load flag texture
    if (!flagTexture.loadFromFile("Source/Resources/Texture/Tileset.png")) {
        // Handle error
        throw std::runtime_error("Failed to load flag texture!");
    }

    initSpritesSheet();

    /*entitySprite.setTexture(flagTexture);
    entitySprite.setTextureRect(spritesSheet[FlagState::SLIDING][0]);

    position.x += 25.f;
    entitySprite.setPosition(position);
    entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);

    originalPosition = entitySprite.getPosition();
    targetPosition = originalPosition;
    targetPosition.y = 300.f;*/

    // Initialize flag
    entitySprite.setTexture(flagTexture);
    entitySprite.setTextureRect(spritesSheet[FlagState::SLIDING][0]);
    position.x += 25.f;
    entitySprite.setPosition(position);
    entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);

    // Initialize pole
    poleSprite.setTexture(flagTexture);
    poleSprite.setTextureRect(sf::IntRect(42, 138, 2, 16));
    poleSprite.setPosition(position.x - 3.f, position.y - 470.f);
    poleSprite.setScale(8, 34);

    // Initialize top sphere
    sphereSprite.setTexture(flagTexture);
    sphereSprite.setTextureRect(sf::IntRect(5, 129, 8, 8));
    sphereSprite.setPosition(position.x - 11.f, position.y - 490.f);
    sphereSprite.setScale(4, 4);

    originalPosition = entitySprite.getPosition();
    targetPosition = originalPosition;
    targetPosition.y = position.y - 470.f;

}

WinFlag::~WinFlag()
{
}
	
void WinFlag::initSpritesSheet() {
    spritesSheet = {
        {FlagState::IDLE, {{1, 358, 14, 16}}},  
        {FlagState::SLIDING, {{1, 341, 14, 16}, {18, 341, 15, 16}}}
    };
}

void WinFlag::update(const float& dt) {
    switch (animationState) {
    case FlagState::IDLE:
        break;

    case FlagState::SLIDING:
        if (isAnimating) {
            animationTimer += dt;

            float progress = std::min(animationTimer / SLIDE_DURATION, 1.0f);
            float newY = originalPosition.y - abs((targetPosition.y - originalPosition.y)) * progress;
            if (newY == targetPosition.y) {
				isAnimating = false;
				animationState = FlagState::COMPLETED;
                return;
			}
            
            entitySprite.setPosition(entitySprite.getPosition().x, newY);

            float frameTime = fmod(animationTimer, ANIMATION_FRAME_DURATION * 2);  
            currentFrame = static_cast<int>(frameTime / ANIMATION_FRAME_DURATION);
            entitySprite.setTextureRect(spritesSheet[FlagState::SLIDING][currentFrame]);

            if (progress >= 4.0f) {
                isAnimating = false;

                animationState = FlagState::COMPLETED;
            }
        }
        break;

    case FlagState::COMPLETED:
        eventMediator->setFinishedLevel(true);
        break;
    }
}

void WinFlag::reactToCollison(int collidedSide) {
    if (collidedSide == Collide_Left || collidedSide == Collide_Top) {
        if (!isAnimating && animationState == FlagState::IDLE) {
            animationState = FlagState::SLIDING;
            isAnimating = true;
            animationTimer = 0.0f;
            currentFrame = 0;
        }
    }
}

void WinFlag::render(sf::RenderTarget* target) {
    target->draw(entitySprite);
    target->draw(poleSprite);
    target->draw(sphereSprite);
    target->draw(hitbox);
}