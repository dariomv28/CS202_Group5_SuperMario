#include "Headers/Heriss.h"
#include "Headers/GameEventMediator.h"

Heriss::Heriss() : Enemy() {
    walkSpeed = 20.0f;

    isAlive = true;
    setHealth(1);

    currentAction = "WALK";
    isAnimationInProgress = false;

    if (!entityTexture.loadFromFile("Source/Resources/texture/Enemies.png")) {
        throw std::runtime_error("Failed to load Heriss texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(4.0f, 4.0f);

    this->animationComponent = new AnimationComponent(this->entitySprite);
    initAnimations();

    movementComponent = new MovementComponent(walkSpeed, 3.0f);

    hitbox.setSize(sf::Vector2f(64.f, 64.f));
    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Blue);
    hitbox.setOutlineThickness(-1.f);
}

Heriss::Heriss(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max) : Heriss() {
    this->position = position;
    this->size = size;
    this->x_min = x_min;
    this->x_max = x_max;
    setMoveRight(true);
}

void Heriss::initAnimations() {
    spritesSheet = {
        // Right movement
        { "WALK-RIGHT-1", sf::IntRect(290, 14, 16, 17) },
        { "WALK-RIGHT-2", sf::IntRect(307, 15, 16, 15) },
        // Left movement
        { "WALK-LEFT-1", sf::IntRect(522, 14, 16, 16) },
        { "WALK-LEFT-2", sf::IntRect(505, 15, 16, 15) }
    };
}

void Heriss::move(const float& dt) {
    this->position += this->movementComponent->velocity * dt;

    if (this->position.x <= x_min) {
        this->position.x = x_min;
        setMoveLeft(false);
        setMoveRight(true);
    }

    if (this->position.x >= x_max) {
        this->position.x = x_max;
        setMoveRight(false);
        setMoveLeft(true);
    }

    this->entitySprite.setPosition(this->position);
    this->hitbox.setPosition(this->position);
}

void Heriss::updateAnimation(const float& dt) {
    if (!isAlive) return;

    if (this->isMoveRight()) {
        animationComponent->setAnimationEnemies("WALK-RIGHT-", spritesSheet, 0.2f);
    }
    else if (this->isMoveLeft()) {
        animationComponent->setAnimationEnemies("WALK-LEFT-", spritesSheet, 0.2f);
    }

    animationComponent->update(dt);
}

bool Heriss::getIsAlive() const {
    return isAlive;
}

void Heriss::setIsAlive(bool alive) {
    isAlive = alive;
}

void Heriss::update(const float& dt) {
    updateAnimation(dt);
    if (!isAlive) {
        disappearDelay += dt;
        if (disappearDelay >= 1.5f) {
            eventMediator->deleteEnemy(this);
        }
        return;
    }
    updateVelocity(dt);
    eventMediator->applyExternalForce(this, dt);
    move(dt);
}

void Heriss::getDamaged() {
    if (!isAlive) return;
    setIsAlive(false);
    eventMediator->increaseScore(300);
}

void Heriss::reactToPlayerCollision(int collidedSide) {
    if (collidedSide == Collide_Top) {
        eventMediator->addPlayerHealth(-1);
        eventMediator->pushPlayerUp();
    }
    else if (collidedSide == Collide_Left) {
        this->setMoveLeft(false);
        this->setMoveRight(true);
        eventMediator->pushPlayerLeft();
    }
    else if (collidedSide == Collide_Right) {
        this->setMoveRight(false);
        this->setMoveLeft(true);
        eventMediator->pushPlayerRight();
    }
}

void Heriss::reactToBlockCollision(int collidedSide) {
    if (collidedSide == Collide_Left) {
        setMoveLeft(false);
        setMoveRight(true);
    }
    else if (collidedSide == Collide_Right) {
        setMoveRight(false);
        setMoveLeft(true);
    }
}
