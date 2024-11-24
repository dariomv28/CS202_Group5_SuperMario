#include "Headers/Mario.h"
#include "Headers/PhysicsEngine.h"
#include <stdexcept>

Mario::Mario(sf::Vector2f position, sf::Vector2f size, int health, int speed, PhysicsEngine* physicEngine)
    : PlayerManager(position, size, health, speed, physicEngine), is_big(false), currentAction("IDLE"), isAnimationInProgress(false) {
    animationComponent = nullptr;
    movementComponent = new MovementComponent(speed, 5.0f);
    init();
}


Mario::~Mario() {
    delete animationComponent;
}

void Mario::init() {
    PlayerManager::init();
    m_name = "Mario";

    if (!entityTexture.loadFromFile("Source/Resources/texture/Mario_Luigi.png")) {
        throw std::runtime_error("Failed to load Mario texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setOrigin(8.0f, 16.0f);
    entitySprite.setScale(4.0f, 4.0f);

    //entitySprite.setPosition(100.f, 500.f);

    animationComponent = new AnimationComponent(entitySprite);
    initAnimations();

    currentAction = "IDLE-";
    animationComponent->setAnimation("IDLE", spritesSheet, 0.2f, is_big);
}

void Mario::initAnimations() {
    spritesSheet = {
        { "IDLE", sf::IntRect(1, 0, 16, 32) },

        { "WALK-1", sf::IntRect(17, 0, 16, 32) },
        { "WALK-2", sf::IntRect(37, 0, 16, 32) },
        { "WALK-3", sf::IntRect(17, 0, 16, 32) },
        { "WALK-4", sf::IntRect(1, 0, 16, 32) },

        { "RUN-1", sf::IntRect(53, 0, 16, 32) },
        //{ "RUN-2", sf::IntRect(69, 0, 16, 32) },
        { "RUN-2", sf::IntRect(17, 0, 16, 32) },
        { "RUN-3", sf::IntRect(37, 0, 16, 32) },
        { "RUN-4", sf::IntRect(17, 0, 16, 32) },
        { "RUN-5", sf::IntRect(1, 0, 16, 32) },

        { "JUMP-1", sf::IntRect(86, 0, 16, 32) },
        { "JUMP-2", sf::IntRect(103, 0, 16, 32) },
        { "JUMP-3", sf::IntRect(120, 0, 16, 32) },

        { "CLIMB-1", sf::IntRect(139, 0, 16, 32) },
        { "CLIMB-2", sf::IntRect(156, 0, 16, 32) },

        { "VICTORY-1", sf::IntRect(171, 0, 16, 32) },
        { "VICTORY-2", sf::IntRect(189, 0, 16, 32) },
        { "VICTORY-3", sf::IntRect(205, 0, 16, 32) },

        { "BECOME_BIG", sf::IntRect(224, 0, 16, 32) },

        { "isBig_IDLE", sf::IntRect(241, 0, 16, 32) },

        { "isBig_WALK-1", sf::IntRect(256, 0, 16, 32) },
        { "isBig_WALK-2", sf::IntRect(273, 0, 16, 32) },
        { "isBig_WALK-3", sf::IntRect(256, 0, 16, 32) },
        { "isBig_WALK-4", sf::IntRect(241, 0, 16, 32) },

        { "isBig_RUN-1", sf::IntRect(290, 0, 16, 32) },
        //{ "isBig_RUN-2", sf::IntRect(307, 0, 16, 32) },
        { "isBig_RUN-2", sf::IntRect(256, 0, 16, 32) },
        { "isBig_RUN-3", sf::IntRect(273, 0, 16, 32) },
        { "isBig_RUN-4", sf::IntRect(256, 0, 16, 32) },
        { "isBig_RUN-5", sf::IntRect(241, 0, 16, 32) },

        { "isBig_JUMP-1", sf::IntRect(328, 0, 20, 32) },
        { "isBig_JUMP-2", sf::IntRect(354, 0, 20, 32) },
        { "isBig_JUMP-3", sf::IntRect(378, 0, 20, 32) },

        { "isBig_CLIMB-1", sf::IntRect(401, 0, 16, 32) },
        { "isBig_CLIMN-2", sf::IntRect(418, 0, 16, 32) },

        { "isBig_CROUCH", sf::IntRect(433, 0, 16, 32) },

        { "isBig_VICTORY-1", sf::IntRect(450, 0, 16, 32) },
        { "isBig_VICTORY-2", sf::IntRect(467, 0, 16, 32) },
        { "isBig_VICTORY-3", sf::IntRect(484, 0, 16, 32) },
        { "isBig_VICTORY-4", sf::IntRect(501, 0, 16, 32) },
    };
}

void Mario::update(const float& dt) {
    handleInput(dt);
    updateAnimation(dt);
    physicsEngine->playerUpdatePhysics(dt);
    updateVelocity(dt);
    move(dt);

}

void Mario::handleInput(const float& dt) {
    movementComponent->isMoveLeft = false;
    movementComponent->isMoveRight = false;
    movementComponent->isJump = false;

    bool isWalking = false;
    bool isRunning = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movementComponent->isMoveLeft = true;
        entitySprite.setScale(-4.0f, 4.0f);
        isWalking = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movementComponent->isMoveRight = true;
        entitySprite.setScale(4.0f, 4.0f);
        isWalking = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        isRunning = true;
    }

    static bool spaceWasPressed = false;
    bool spaceIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

    if (spaceIsPressed && !spaceWasPressed) {
        movementComponent->isJump = true;
        currentAction = "JUMP-";
        isAnimationInProgress = true;

        // Reset animation when starting a new jump (either first or second)
        if (!movementComponent->onGround && movementComponent->getJumpsRemaining() > 0) {
            // Reset animation for double jump
            animationComponent->currentFrameIndex = 0;
            animationComponent->elapsedTime = 0;
        }
    }
    spaceWasPressed = spaceIsPressed;

    // Only change animation if we're not already jumping
    if (currentAction != "JUMP-") {
        if (isWalking && isRunning) {
            currentAction = "RUN-";
        }
        else if (isWalking) {
            currentAction = "WALK-";
        }
        else {
            currentAction = "IDLE";
        }
    }
}

void Mario::updateAnimation(const float& dt) {
    std::string prefix = is_big ? "isBig_" : "";
    bool animationSet = false;

    if (currentAction == "JUMP-") {
        // Use a faster animation speed to make sure we see the jump frames
        animationComponent->setAnimation(prefix + "JUMP-", spritesSheet, 0.2f, is_big);
        animationSet = true;

        // If the jump animation has completed and we're on the ground
        if (animationComponent->currentFrameIndex == animationComponent->currentAnimationFrames.size() - 1
            && movementComponent->onGround) {
            currentAction = "IDLE";
        }
    }
    else if (currentAction == "RUN-") {
        animationComponent->setAnimation(prefix + "RUN-", spritesSheet, 0.15f, is_big);
        animationSet = true;
    }
    else if (currentAction == "WALK-") {
        animationComponent->setAnimation(prefix + "WALK-", spritesSheet, 0.2f, is_big);
        animationSet = true;
    }
    else if (currentAction == "CROUCH") {
        animationComponent->setAnimation(prefix + "CROUCH", spritesSheet, 0.2f, is_big);
        animationSet = true;
    }

    if (!animationSet) {
        animationComponent->setAnimation(prefix + "IDLE", spritesSheet, 0.5f, is_big);
    }

    animationComponent->update(0.016f);
}

void Mario::render(sf::RenderTarget* target) {
    if (target) {
        target->draw(entitySprite);
    }
    else {
        std::cerr << "Render target is null!" << std::endl;
    }
}

bool Mario::getIsBig() const {
    return is_big;
}
