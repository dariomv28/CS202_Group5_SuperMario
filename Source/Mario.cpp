#include "Headers/Mario.h"
#include "Headers/PhysicsEngine.h"
#include <stdexcept>

Mario::Mario(): PlayerManager(sf::Vector2f(0,0), sf::Vector2f(CELL_SIZE, CELL_SIZE), 3, 30.f), 
                currentAction("IDLE"), isAnimationInProgress(false) 
{
    animationComponent = nullptr;
    movementComponent = new MovementComponent(30.f, 4.0f);
    init();
}

Mario::Mario(sf::Vector2f position, sf::Vector2f size, int health, int speed)
    : PlayerManager(position, size, health, speed), currentAction("IDLE"), isAnimationInProgress(false) {
    animationComponent = nullptr;
    movementComponent = new MovementComponent(speed, 4.0f);
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
    entitySprite.setScale(4.0f, 4.0f);
        
    this->animationComponent = new AnimationComponent(this->entitySprite);
    initAnimations();

    if (!is_big) {
        hitbox.setSize(sf::Vector2f(64.f, 64.f));
        //hitbox.setOrigin(32.f, 32.f);
        hitbox.setPosition(position);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(-1.f);

        currentAction = "IDLE-";
        animationComponent->setAnimation("IDLE", spritesSheet, 0.2f, is_big);
    }
    else {
        hitbox.setSize(sf::Vector2f(64.f, 125.f));
        //hitbox.setOrigin(32.f, 64.f);  
        hitbox.setPosition(position);
        hitbox.setFillColor(sf::Color::Transparent);
        hitbox.setOutlineColor(sf::Color::Red);
        hitbox.setOutlineThickness(-1.f);

        currentAction = "isBig_IDLE-";
        animationComponent->setAnimation("isBig_IDLE", spritesSheet, 0.2f, is_big);
    }
}

void Mario::initAnimations() {
    spritesSheet = {
        { "IDLE", sf::IntRect(1, 17, 16, 16) },

        { "WALK-1", sf::IntRect(17, 17, 16, 16) },
        { "WALK-2", sf::IntRect(37, 17, 16, 16) },
        { "WALK-3", sf::IntRect(17, 17, 16, 16) },
        { "WALK-4", sf::IntRect(1, 17, 16, 16) },

        { "RUN-1", sf::IntRect(53, 17, 16, 16) },
        //{ "RUN-2", sf::IntRect(69, 0, 16, 32) },
        { "RUN-2", sf::IntRect(17, 17, 16, 16) },
        { "RUN-3", sf::IntRect(37, 17, 16, 16) },
        { "RUN-4", sf::IntRect(17, 17, 16, 16) },
        { "RUN-5", sf::IntRect(1, 17, 16, 16) },

        { "JUMP-1", sf::IntRect(86, 17, 16, 16) },
        { "JUMP-2", sf::IntRect(103, 17, 16, 16) },
        { "JUMP-3", sf::IntRect(120, 17, 16, 16) },

        { "CLIMB-1", sf::IntRect(139, 17, 16, 16) },
        { "CLIMB-2", sf::IntRect(156, 17, 16, 16) },

        { "VICTORY-1", sf::IntRect(171, 17, 16, 16) },
        { "VICTORY-2", sf::IntRect(189, 17, 16, 16) },
        { "VICTORY-3", sf::IntRect(205, 17, 16, 16) },

        { "BECOME_BIG", sf::IntRect(224, 3, 16, 32) },

        { "isBig_IDLE", sf::IntRect(241, 3, 16, 32) },

        { "isBig_WALK-1", sf::IntRect(256, 3, 16, 32) },
        { "isBig_WALK-2", sf::IntRect(273, 3, 16, 32) },
        { "isBig_WALK-3", sf::IntRect(256, 3, 16, 32) },
        { "isBig_WALK-4", sf::IntRect(241, 3, 16, 32) },

        { "isBig_RUN-1", sf::IntRect(290, 3, 16, 32) },
        //{ "isBig_RUN-2", sf::IntRect(307, 0, 16, 32) },
        { "isBig_RUN-2", sf::IntRect(256, 3, 16, 32) },
        { "isBig_RUN-3", sf::IntRect(273, 3, 16, 32) },
        { "isBig_RUN-4", sf::IntRect(256, 3, 16, 32) },
        { "isBig_RUN-5", sf::IntRect(241, 3, 16, 32) },

        { "isBig_JUMP-1", sf::IntRect(328, 3, 20, 32) },
        { "isBig_JUMP-2", sf::IntRect(354, 3, 20, 32) },
        { "isBig_JUMP-3", sf::IntRect(378, 3, 20, 32) },

        { "isBig_CLIMB-1", sf::IntRect(401, 3, 16, 32) },
        { "isBig_CLIMN-2", sf::IntRect(418, 3, 16, 32) },

        { "isBig_CROUCH", sf::IntRect(433, 3, 16, 32) },

        { "isBig_VICTORY-1", sf::IntRect(450, 3, 16, 32) },
        { "isBig_VICTORY-2", sf::IntRect(467, 3, 16, 32) },
        { "isBig_VICTORY-3", sf::IntRect(484, 3, 16, 32) },
        { "isBig_VICTORY-4", sf::IntRect(501, 3, 16, 32) },
    };
}

void Mario::update(const float& dt) {
	/*std::cout << this->position.x << " " << this->position.y << std::endl;
    sf::FloatRect cur = (this->hitbox.getGlobalBounds());
    std::cerr << cur.getPosition().x << " " << cur.getPosition().y << "\n";*/
    updateAnimation(dt);
    updateVelocity(dt);
    //std::cerr << this->getPosition().x << " "<< this->getPosition().y << std::endl;
	eventMediator->applyExternalForce(this, dt);
    move(dt);
    //apply buffs
    for (auto& buff : buffs) {
		buff->applyBuff(this, this->eventMediator);
	}
}

void Mario::handleInput(const float& dt) {
    // Reset movement flags
    movementComponent->isMoveLeft = false;
    movementComponent->isMoveRight = false;
    movementComponent->isJump = false;

    bool isWalking = false;
    bool isRunning = false;
    bool isCrouching = false;

    // Simultaneous movement and jump handling
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movementComponent->isMoveLeft = true;
        entitySprite.setScale(4.0f, 4.0f);
        //hitbox.setScale(1.0f, 1.0f);
        isWalking = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movementComponent->isMoveRight = true;
        entitySprite.setScale(4.0f, 4.0f);
        //hitbox.setScale(1.0f, 1.0f);
        isWalking = true;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if (is_big) {
            currentAction = "CROUCH";
            isAnimationInProgress = true;
            isCrouching = true;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
        isRunning = true;
    }

    // Improved jump handling
    static bool spaceWasPressed = false;
    bool spaceIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

    // Immediate jump request when space is first pressed
    if (spaceIsPressed && !spaceWasPressed) {
        if (movementComponent->getJumpsRemaining() > 0) {
            eventMediator->playJumpSound();
        }
        movementComponent->isJump = true;
        currentAction = "JUMP-";
        isAnimationInProgress = true;

        // Reset jump animation if needed
        if (!movementComponent->onGround && movementComponent->getJumpsRemaining() > 0) {
            animationComponent->currentFrameIndex = 0;
            animationComponent->elapsedTime = 0;
        }
    }
    spaceWasPressed = spaceIsPressed;

    // Animation and action state management
    if (currentAction != "JUMP-") {
        if (isWalking && isRunning) {
            currentAction = "RUN-";
        }
        else if (isWalking) {
            currentAction = "WALK-";
        }
        else if (isCrouching) {
            currentAction = "CROUCH";
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
        target->draw(hitbox);
        //std::cout << this->getOnGround() << std::endl;
    }
    else {
        std::cerr << "Render target is null!" << std::endl;
    }
}

bool Mario::getIsBig() const {
    return is_big;
}
