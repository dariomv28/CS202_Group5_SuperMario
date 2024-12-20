#include "Headers/Mario.h"
#include "Headers/PhysicsEngine.h"
#include <stdexcept>

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

    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1.f);
    updateHitboxSize();

    currentAction = "IDLE";
}

void Mario::initAnimations() {
	std::unordered_map<std::string, sf::IntRect> idle = {
		{"IDLE", allSpritesMario["IDLE"]},
	};

    std::unordered_map<std::string, sf::IntRect> walk1 = {
        {"WALK-1", allSpritesMario["WALK-1"]},
        {"WALK-2", allSpritesMario["WALK-2"]},
		{"WALK-3", allSpritesMario["WALK-1"]},
		{"WALK-4", allSpritesMario["IDLE"]},
    };

    std::unordered_map<std::string, sf::IntRect> stop = {
        {"STOP", allSpritesMario["STOP"]},
    };

    std::unordered_map<std::string, sf::IntRect> run1 = {
        {"RUN-1", allSpritesMario["RUN-1"] },
		{"RUN-2", allSpritesMario["WALK-1"] },
		{"RUN-3", allSpritesMario["WALK-2"] },
        {"RUN-4", allSpritesMario["WALK-1"] },
		{"RUN-5", allSpritesMario["IDLE"] },
	};

	std::unordered_map<std::string, sf::IntRect> jump = {
		{"JUMP-1", allSpritesMario["JUMP-1"]},
		{"JUMP-2", allSpritesMario["JUMP-2"]},
		{"JUMP-3", allSpritesMario["JUMP-3"]},
	};

	std::unordered_map<std::string, sf::IntRect> climb = {
		{"CLIMB-1", allSpritesMario["CLIMB-1"]},
		{"CLIMB-2", allSpritesMario["CLIMB-2"]},
	};

	std::unordered_map<std::string, sf::IntRect> victory = {
		{"VICTORY-1", allSpritesMario["VICTORY-1"]},
		{"VICTORY-2", allSpritesMario["VICTORY-2"]},
		{"VICTORY-3", allSpritesMario["VICTORY-3"]},
	};

    std::unordered_map<std::string, sf::IntRect> becomeBig = {
        {"BECOME_BIG", allSpritesMario["BECOME_BIG"]},
    };

	std::unordered_map<std::string, sf::IntRect> isBigIdle = {
		{"isBig_IDLE", allSpritesMario["isBig_IDLE"]},
	};

	std::unordered_map<std::string, sf::IntRect> isBigWalk1 = {
		{"isBig_WALK-1", allSpritesMario["isBig_WALK-1"]},
		{"isBig_WALK-2", allSpritesMario["isBig_WALK-2"]},
		{"isBig_WALK-3", allSpritesMario["isBig_WALK-1"]},
		{"isBig_WALK-4", allSpritesMario["isBig_IDLE"]},
	};

	std::unordered_map<std::string, sf::IntRect> isBigStop = {
		{"isBig_STOP", allSpritesMario["isBig_STOP"]},
	};

	std::unordered_map<std::string, sf::IntRect> isBigRun1 = {
		{"isBig_RUN-1", allSpritesMario["isBig_RUN-1"]},
        {"isBig_RUN-2", allSpritesMario["isBig_WALK-1"]},
        {"isBig_RUN-3", allSpritesMario["isBig_WALK-2"]},
		{"isBig_RUN-4", allSpritesMario["isBig_WALK-1"]},
		{"isBig_RUN-5", allSpritesMario["isBig_IDLE"]},
	};

	std::unordered_map<std::string, sf::IntRect> isBigJump = {
		{"isBig_JUMP-1", allSpritesMario["isBig_JUMP-1"]},
		{"isBig_JUMP-2", allSpritesMario["isBig_JUMP-2"]},
		{"isBig_JUMP-3", allSpritesMario["isBig_JUMP-3"]},
	};

	std::unordered_map<std::string, sf::IntRect> isBigClimb = {
		{"isBig_CLIMB-1", allSpritesMario["isBig_CLIMB-1"]},
		{"isBig_CLIMB-2", allSpritesMario["isBig_CLIMB-2"]},
	};

	std::unordered_map<std::string, sf::IntRect> isBigCrouch = {
		{"isBig_CROUCH", allSpritesMario["isBig_CROUCH"]},
	};

	std::unordered_map<std::string, sf::IntRect> isBigVictory = {
		{"isBig_VICTORY-1", allSpritesMario["isBig_VICTORY-1"]},
		{"isBig_VICTORY-2", allSpritesMario["isBig_VICTORY-2"]},
		{"isBig_VICTORY-3", allSpritesMario["isBig_VICTORY-3"]},
		{"isBig_VICTORY-4", allSpritesMario["isBig_VICTORY-4"]},
	};
	
	spritesSheet.insert(idle.begin(), idle.end());
	spritesSheet.insert(walk1.begin(), walk1.end());
	spritesSheet.insert(stop.begin(), stop.end());
	spritesSheet.insert(run1.begin(), run1.end());
	spritesSheet.insert(jump.begin(), jump.end());
	spritesSheet.insert(climb.begin(), climb.end());
	spritesSheet.insert(victory.begin(), victory.end());
	spritesSheet.insert(becomeBig.begin(), becomeBig.end());

    spritesSheet.insert(isBigIdle.begin(), isBigIdle.end());
    spritesSheet.insert(isBigWalk1.begin(), isBigWalk1.end());
    spritesSheet.insert(isBigStop.begin(), isBigStop.end());
    spritesSheet.insert(isBigRun1.begin(), isBigRun1.end());
    spritesSheet.insert(isBigJump.begin(), isBigJump.end());
    spritesSheet.insert(isBigClimb.begin(), isBigClimb.end());
    spritesSheet.insert(isBigCrouch.begin(), isBigCrouch.end());
    spritesSheet.insert(isBigVictory.begin(), isBigVictory.end());
}

void Mario::update(const float& dt) {
    updateAnimation(dt);
	updateHitboxSize();
    updateVelocity(dt);
	eventMediator->applyExternalForce(this, dt);
    move(dt);
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

    if (isRunning) {
		movementComponent->maxVelocity = 4.0f * 100 + 150.0f;
    }
    else {
		movementComponent->maxVelocity = 4.0f * 100;
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

void Mario::setBig(bool big) {
    if (is_big != big) {  
        is_big = big;
        updateHitboxSize();
        currentAction = "IDLE";
        animationComponent->setAnimation(is_big ? "isBig_IDLE" : "IDLE", spritesSheet, 0.5f, is_big);
    }
}

void Mario::updateHitboxSize() {
	if (is_big) {
		if (currentAction == "JUMP-") {
			hitbox.setSize(sf::Vector2f(80.f, 128.f));
		}
		else if (currentAction == "CROUCH") {
			hitbox.setSize(sf::Vector2f(64.f, 120.f));
		}
        else {
            hitbox.setSize(sf::Vector2f(64.f, 122.f));
        }
	}
	else {
        hitbox.setSize(sf::Vector2f(64.f, 64.f));
	}
	hitbox.setPosition(position);
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
