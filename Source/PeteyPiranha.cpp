#include "Headers/PeteyPiranha.h"
#include "Headers/GameEventMediator.h"

PeteyPiranha::PeteyPiranha() : Enemy() {
    this->movementComponent = new MovementComponent(0.f, 0.f);
    isAlive = true;
    isMouthOpen = false;
    mouthTimer = 0.0f;
    switchInterval = 2.0f;
    hasDamagedPlayer = false;

    setHealth(1);

    if (!entityTexture.loadFromFile("Source/Resources/texture/Enemies.png")) {
        throw std::runtime_error("Failed to load Petey Piranha texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(4.0f, 4.0f);

    this->animationComponent = new AnimationComponent(this->entitySprite);
    initSprites();

    hitbox.setSize(sf::Vector2f(64.f, 96.f));
    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1.f);
}

PeteyPiranha::PeteyPiranha(sf::Vector2f position, sf::Vector2f size) : PeteyPiranha() {
    this->position = position;
    this->size = size;
}

void PeteyPiranha::initSprites() {
    spritesSheet = {
        { "MOUTH-OPEN", sf::IntRect(205, 37, 16, 24) },
        { "MOUTH-CLOSED", sf::IntRect(222, 37, 16, 24) }
    };
}

void PeteyPiranha::update(const float& dt) {
    mouthTimer += dt;


    if (mouthTimer >= switchInterval) {
        isMouthOpen = !isMouthOpen;
        mouthTimer = 0.0f;

        hasDamagedPlayer = false;
    }


    updateAnimation(dt);


    entitySprite.setPosition(position);
    hitbox.setPosition(position);
}

bool PeteyPiranha::getIsAlive() const {
    return isAlive;
}

void PeteyPiranha::setIsAlive(bool alive) {
    isAlive = alive;
}

void PeteyPiranha::getDamaged() {

}

void PeteyPiranha::reactToPlayerCollision(int collidedSide) {
    if (collidedSide == Collide_Top) {
        if (isMouthOpen && !hasDamagedPlayer) {

            eventMediator->damagePlayer(-1);
            hasDamagedPlayer = true;
        }
    }
}

void PeteyPiranha::reactToBlockCollision(int collidedSide) {

}

void PeteyPiranha::updateAnimation(const float& dt) {
    if (!isAlive) {
        return;
    }

    if (isMouthOpen) {

        animationComponent->setAnimationEnemies("MOUTH-OPEN", spritesSheet, 0.2f);
    }
    else {

        animationComponent->setAnimationEnemies("MOUTH-CLOSED", spritesSheet, 0.2f);
    }


    animationComponent->update(dt);
}