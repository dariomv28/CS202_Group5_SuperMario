#include "Headers/FlyingKoopa.h"

FlyingKoopa::FlyingKoopa()
{
    //walkSpeed = 20.f;

    //isAlive = true;
    setHealth(1);

    //currentAction = "WALK";
   // isAnimationInProgress = false;
    //isShelled = false;
    //shellTimer = 0.0f;

    if (!entityTexture.loadFromFile("Source/Resources/texture/Enemies.png")) {
        throw std::runtime_error("Failed to load Koopa texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(4.0f, 4.0f);


    this->animationComponent = new AnimationComponent(this->entitySprite);
    initAnimations();

   // movementComponent = new MovementComponent(walkSpeed, 3.0f);

    hitbox.setSize(sf::Vector2f(64.f, 96.f));
    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Green);
    hitbox.setOutlineThickness(-1.f);
}

FlyingKoopa::FlyingKoopa(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max) : FlyingKoopa()
{
	initAnimations();
}

void FlyingKoopa::initAnimations() {
    spritesSheet = {
        { "FLY-1", sf::IntRect(86, 37, 16, 24) },    // Green Koopa walking frame 1
        { "FLY-2", sf::IntRect(103, 38, 16, 23) },   // Green Koopa walking frame 2

        { "FLYR-1", sf::IntRect(726, 37, 16, 24) },
        { "FLYR-2", sf::IntRect(709, 38, 16, 23) },

     //   { "SHELL-STOP", sf::IntRect(188, 45, 16, 14) },    // Koopa in shell
     //   { "SHELL-MOVING-1", sf::IntRect(120, 45, 16, 14) }, // Koopa shell moving frame 1
     //   { "SHELL-MOVING-2", sf::IntRect(137, 45, 16, 14) },  // Koopa shell moving frame 2
     //   { "SHELL-MOVING-3", sf::IntRect(154, 45, 16, 14) },  // Koopa shell moving frame 3
     //   { "SHELL-MOVING-4", sf::IntRect(171, 45, 16, 14) }   // Koopa shell moving frame 4
    };
}

void FlyingKoopa::move(const float& dt)
{
}

void FlyingKoopa::updateAnimation(const float& dt)
{

}

void FlyingKoopa::update(const float& dt)
{
}

void FlyingKoopa::getDamaged()
{
}

void FlyingKoopa::reactToPlayerCollision(int collidedSide)
{
}

void FlyingKoopa::reactToBlockCollision(int collidedSide)
{
}

bool FlyingKoopa::getIsAlive() const
{
	return isAlive;
}

void FlyingKoopa::setIsAlive(bool alive)
{
	isAlive = alive;
}


