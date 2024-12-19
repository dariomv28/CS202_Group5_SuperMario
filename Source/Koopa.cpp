#include "Headers/Koopa.h"
#include "Headers/GameEventMediator.h"

Koopa::Koopa() : Enemy() {
    walkSpeed = 20.f;

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
    entitySprite.setScale(4.0f, 4.0f);


    this->animationComponent = new AnimationComponent(this->entitySprite);
    initAnimations();

    movementComponent = new MovementComponent(walkSpeed, 3.0f);

    hitbox.setSize(sf::Vector2f(64.f, 96.f));
    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Green);
    hitbox.setOutlineThickness(-1.f);
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
        { "SHELL-STOP", sf::IntRect(188, 45, 16, 14) },    // Koopa in shell
		{ "SHELL-MOVING-1", sf::IntRect(120, 45, 16, 14) }, // Koopa shell moving frame 1
		{ "SHELL-MOVING-2", sf::IntRect(137, 45, 16, 14) },  // Koopa shell moving frame 2
		{ "SHELL-MOVING-3", sf::IntRect(154, 45, 16, 14) },  // Koopa shell moving frame 3
		{ "SHELL-MOVING-4", sf::IntRect(171, 45, 16, 14) }   // Koopa shell moving frame 4
    };
}

void Koopa::move(const float& dt)
{

    this->position += this->movementComponent->velocity * dt;

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

    this->entitySprite.setPosition(this->position);
    this->hitbox.setPosition(this->position);
}

void Koopa::update(const float& dt) {
    updateAnimation(dt);
    updateVelocity(dt);
    eventMediator->applyExternalForce(this, dt);

    if (isAlive && isShelled) {
        shellTimer += dt;
        if (shellTimer >= 5.0f) {  // Exit shell state after 5 seconds
            this->hitbox.setSize(sf::Vector2f(64.f, 96.f));
            this->movementComponent->acceleration = walkSpeed;
            shellTimer = 0.0f;

            setIsAlive(true);
            setIsShelled(false);
        }
    }

    if (!isAlive) {
        this->movementComponent->acceleration = walkSpeed;
        disappearDelay += dt;
        if (disappearDelay >= 1.0f) {
            eventMediator->deleteEnemy(this);
        }
    }
    move(dt);
}

void Koopa::reactToBlockCollision(int collidedSide) {
	if (collidedSide == Collide_Left) {
		setMoveLeft(false);
		setMoveRight(true);
	}
	else if (collidedSide == Collide_Right) {
		setMoveRight(false);
		setMoveLeft(true);
	}
}

void Koopa::updateAnimation(const float& dt) {
    if (!isAlive) {
        animationComponent->setAnimationEnemies("SHELL-MOVING-", spritesSheet, 0.2f);
    }
    else if (isShelled) {
        if (shellTimer > 0.0f) {
            animationComponent->setAnimationEnemies("SHELL-STOP", spritesSheet, 0.2f);
        }
        else {
            animationComponent->setAnimationEnemies("SHELL-MOVING-", spritesSheet, 0.2f);
        }
    }
    else {
        animationComponent->setAnimationEnemies("WALK-", spritesSheet, 0.2f);
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
            isShelled = true;
            shellTimer = 0.0f;
            this->hitbox.setSize(sf::Vector2f(64.f, 56.f));
            this->movementComponent->acceleration = 0;
            eventMediator->increaseScore(200);
        }
        else if (shellTimer > 3.0f) {
            isAlive = false;
            isShelled = false;
            this->hitbox.setSize(sf::Vector2f(64.f, 56.f));

            eventMediator->increaseScore(400);
        }
    }
    else {
        if (collidedSide == Collide_Left)
        {
            this->setMoveLeft(false);
            this->setMoveRight(true);
            eventMediator->pushPlayerLeft();
        }
        else
        {
            this->setMoveRight(false);
            this->setMoveLeft(true);
            eventMediator->pushPlayerRight();
        }
        eventMediator->decreasePlayerHealth();
    }
}

// Getter for shelled state
bool Koopa::getIsShelled() const {
    return isShelled;
}

// Setter for shelled state
void Koopa::setIsShelled(bool shelled) {
	isShelled = shelled;
}

// Set the sprite scale based on the animation name
void Koopa::setScaleSprite(std::string name) {
   
}