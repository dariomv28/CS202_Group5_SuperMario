#include "Headers/FlyingKoopa.h"
#include "Headers/Bullet.h"

FlyingKoopa::FlyingKoopa(): Enemy()
{
    walkSpeed = 20.f;

    isAlive = true;
    setHealth(1);

    /*currentAction = "WALK";
    isAnimationInProgress = false;
    isShelled = false;
    shellTimer = 0.0f;*/

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

FlyingKoopa::FlyingKoopa(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max) : FlyingKoopa()
{
	this->position = position;
	this->size = size;
	this->x_min = x_min;
	this->x_max = x_max;
    this->movementComponent->preventFalling = 2500;
	setMoveRight(true);
	//initAnimations();
}

FlyingKoopa::FlyingKoopa(sf::Vector2f position, sf::Vector2f size) : FlyingKoopa()
{
    this->position = position;
    this->size = size;
    this->x_min = position.x - 300.f;
    this->x_max = position.x + 300.f;
    this->movementComponent->preventFalling = 2500;
    setMoveRight(true);
    //initAnimations();
}

void FlyingKoopa::initAnimations() {
    spritesSheet = {
        { "FLY-1", sf::IntRect(86, 37, 16, 24) },    // Green Koopa walking frame 1
        { "FLY-2", sf::IntRect(103, 38, 16, 23) },   // Green Koopa walking frame 2

        { "FLYR-1", sf::IntRect(726, 37, 16, 24) },
        { "FLYR-2", sf::IntRect(709, 38, 16, 23) },

        //{ "SHELL-STOP", sf::IntRect(188, 45, 16, 14) },    // Koopa in shell
        { "SHELL-MOVING-1", sf::IntRect(120, 45, 16, 14) }, // Koopa shell moving frame 1
        { "SHELL-MOVING-2", sf::IntRect(137, 45, 16, 14) },  // Koopa shell moving frame 2
        { "SHELL-MOVING-3", sf::IntRect(154, 45, 16, 14) },  // Koopa shell moving frame 3
        { "SHELL-MOVING-4", sf::IntRect(171, 45, 16, 14) }   // Koopa shell moving frame 4
    };
}

void FlyingKoopa::move(const float& dt)
{
	this->position += this->movementComponent->velocity * dt;

    if (this->position.x <= x_min) {
        this->position.x = std::max<float>(this->position.x, x_min);

        setMoveLeft(false);
        setMoveRight(true);
    }

    if (this->position.x >= x_max) {
        this->position.x = std::min<float>(this->position.x, x_max);

        setMoveRight(false);
        setMoveLeft(true);
    }

    this->entitySprite.setPosition(this->position);
    this->hitbox.setPosition(this->position);
}

void FlyingKoopa::updateAnimation(const float& dt)
{
    if (!isAlive) {
        animationComponent->setAnimationEnemies("SHELL-MOVING-", spritesSheet, 0.2f);
    }
    else
    {
        if (this->isMoveLeft()) {
            animationComponent->setAnimationEnemies("FLYR-", spritesSheet, 0.2f);
        }
        else if (this->isMoveRight()) {
            animationComponent->setAnimationEnemies("FLY-", spritesSheet, 0.2f);
        }
    }
    animationComponent->update(dt);
}

void FlyingKoopa::updateShooting(const float& dt) {
    if (reloadTimer < reloadFire) {
        reloadTimer += dt;
    }
    else {
        reloadTimer = 0;
        std::cerr << "Bowser shoot" << std::endl;
        sf::Vector2f directionVector = sf::Vector2f(eventMediator->getPlayerPosition().x - this->getPosition().x,
            eventMediator->getPlayerPosition().y - this->getPosition().y);
        float length = sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
        sf::Vector2f direction = sf::Vector2f(directionVector.x / length, directionVector.y / length);
        sf::Vector2f bulletVelocity = sf::Vector2f(direction.x * 400.f, direction.y * 400.f);
        eventMediator->spawnPowerUp(new Bullet(this->getCenter(), sf::Vector2f(20, 20),
            "bullet", "enemy", bulletVelocity));
    }
}

void FlyingKoopa::update(const float& dt)
{
    updateAnimation(dt);
    updateVelocity(dt);
    eventMediator->applyExternalForce(this, dt);

    //if (isAlive && isShelled) {
    //    shellTimer += dt;
    //    if (shellTimer >= 5.0f) {  // Exit shell state after 5 seconds
    //        this->hitbox.setSize(sf::Vector2f(64.f, 96.f));
    //        this->movementComponent->acceleration = walkSpeed * 100;
    //        shellTimer = 0.0f;

    //        setIsAlive(true);
    //        setIsShelled(false);
    //    }
    //}

    if (!isAlive) {
        this->movementComponent->preventFalling = 0;
		//this->movementComponent->velocity = sf::Vector2f(0.0f, 0.0f);
        this->movementComponent->acceleration = 0;
        disappearDelay += dt;
        if (disappearDelay >= 3.0f) {
            eventMediator->deleteEnemy(this);
        }
    }
	else {
		updateShooting(dt);
	}
    move(dt);
}

void FlyingKoopa::getDamaged()
{
    isAlive = false;
    //isShelled = false;
    this->hitbox.setSize(sf::Vector2f(64.f, 56.f));
    eventMediator->increaseScore(400);
}

void FlyingKoopa::reactToPlayerCollision(int collidedSide)
{
    if (collidedSide == Collide_Left) {
        setMoveLeft(false);
        setMoveRight(true);
        eventMediator->pushPlayerLeft();
    }
    else if (collidedSide == Collide_Right) {
        setMoveRight(false);
        setMoveLeft(true);
        eventMediator->pushPlayerRight();
    }
    eventMediator->damagePlayer(-1);
}

void FlyingKoopa::reactToBlockCollision(int collidedSide)
{
    if (collidedSide == Collide_Left)
    {
        this->setMoveLeft(false);
        this->setMoveRight(true);
    }
    else
    {
        this->setMoveRight(false);
        this->setMoveLeft(true);
    }
}

bool FlyingKoopa::getIsAlive() const
{
	return isAlive;
}

void FlyingKoopa::setIsAlive(bool alive)
{
	isAlive = alive;
}


