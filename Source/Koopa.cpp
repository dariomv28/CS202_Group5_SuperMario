#include "Headers/Koopa.h"
#include "Headers/GameEventMediator.h"

Koopa::Koopa() : Enemy() {
    walkSpeed = 17.0f;  // Slightly faster than Goomba

    isAlive = true;
    setHealth(1);

    currentAction = "WALK";
    isAnimationInProgress = false;
    isShelled = false;
    shellTimer = 0.0f;

    if (!entityTexture.loadFromFile("Source/Resources/texture/Enemies.png")) {
        throw std::runtime_error("Failed to load Koopa texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(4.0f, 2.6f);


    this->animationComponent = new AnimationComponent(this->entitySprite);
    initAnimations();

    movementComponent = new MovementComponent(walkSpeed, 5.0f);

    hitbox.setSize(sf::Vector2f(64.f, 64.f));
    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Green);
    hitbox.setOutlineThickness(1.f);
}

Koopa::Koopa(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max) : Koopa() {
    this->position = position;
    this->size = size;
    this->x_min = x_min;
    this->x_max = x_max;
    setMoveRight(true);
}

void Koopa::initAnimations() {
    spritesSheet = {
        { "WALK-1", sf::IntRect(52, 37, 16, 24) },    // Green Koopa walking frame 1
        { "WALK-2", sf::IntRect(69, 38, 16, 23) },   // Green Koopa walking frame 2
        { "SHELL", sf::IntRect(188, 45, 16, 14) },    // Koopa in shell
		{ "SHELL-MOVING-1", sf::IntRect(120, 45, 16, 14) }, // Koopa shell moving frame 1
		{ "SHELL-MOVING-2", sf::IntRect(137, 45, 16, 14) },  // Koopa shell moving frame 2
		{ "SHELL-MOVING-3", sf::IntRect(154, 45, 16, 14) },  // Koopa shell moving frame 3
		{ "SHELL-MOVING-4", sf::IntRect(171, 45, 16, 14) }   // Koopa shell moving frame 4
    };
}

void Koopa::move(const float& dt)
{
    // Handle shell state
    if (isShelled) {
        shellTimer += dt;
        if (shellTimer >= 5.0f) {  // Exit shell state after 5 seconds
			isShelled = false;
			this->hitbox.setSize(sf::Vector2f(64.f, 64.f));
			this->movementComponent->acceleration = 0;
			shellTimer = 0.0f;
        }
    }

    if (!isAlive) {
        shellTimer += dt;
        this->movementComponent->acceleration = 2.0f;
		this->hitbox.setSize(sf::Vector2f(64.f, 32.f));
		if (shellTimer >= 1.5f) {
			eventMediator->deleteEnemy(this);
		}
    }

    // If not in shell, move normally like Goomba
    if (!isShelled) {
        this->position += this->movementComponent->velocity;

        if (this->position.x <= x_min) {
            this->position.x = std::max<float>(this->position.x, x_min);
			
			setScaleSprite("RIGHT");

            setMoveLeft(false);
            setMoveRight(true);
        }

        if (this->position.x >= x_max) {
            this->position.x = std::min<float>(this->position.x, x_max);
            
            setScaleSprite("LEFT");

            setMoveRight(false);
            setMoveLeft(true);
        }
    }

    this->entitySprite.setPosition(this->position);
    this->hitbox.setPosition(this->position);
}

void Koopa::updateAnimation(const float& dt) {
    if (isAlive) {
        if (!isShelled) {
            // Normal walking animation
            animationComponent->setAnimationEnemies("WALK-", spritesSheet, 0.2f);
        }
        else {
            // In shell state
            animationComponent->setAnimationEnemies("SHELL", spritesSheet, 0.2f);
        }
    }
    else {
		// Dead Koopa
		animationComponent->setAnimationEnemies("SHELL-MOVING-", spritesSheet, 0.2f);
    }
    animationComponent->update(dt);
}

bool Koopa::getIsAlive() const {
    return isAlive;
}

void Koopa::setIsAlive(bool alive) {
    isAlive = alive;
}

void Koopa::reactToPlayerCollision(int collidedSide) {
    if (collidedSide == Collide_Top) {
        if (!isShelled) {
            // First hit puts Koopa in shell
            isShelled = true;
            this->hitbox.setSize(sf::Vector2f(64.f, 32.f));
            this->movementComponent->acceleration = 0;
            eventMediator->increaseScore(200);
        }
        else {
            // Second hit kills the Koopa
            shellTimer = 0;
            setIsAlive(false);
            eventMediator->increaseScore(400);
        }
    }
    else {
        // Side collision
        if (isShelled) {
            // Sliding shell can damage other enemies
            walkSpeed = 64.0f;  // High-speed shell slide
            // You might want to add logic to damage other enemies here
        }
        else {
            // Normal Koopa side collision hurts player
            if (collidedSide == Collide_Left) eventMediator->pushPlayerLeft();
            else eventMediator->pushPlayerRight();
            eventMediator->decreasePlayerHealth();
        }
    }
}

// Getter for shelled state
bool Koopa::getIsShelled() const {
    return isShelled;
}

// Set the sprite scale based on the animation name
void Koopa::setScaleSprite(std::string name) {
    if (name == "LEFT") {
		entitySprite.setScale(-4.0f, 2.6f);
		hitbox.setScale(-1.0f, 1.0f);
	}
    else if (name == "RIGHT") {
        entitySprite.setScale(4.0f, 2.6f);
        hitbox.setScale(1.0f, 1.0f);
    }
}