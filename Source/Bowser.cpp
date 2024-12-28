#include "Headers/Bowser.h"
#include "Headers/Rocket.h"
#include "Headers/Bullet.h"
#include "Headers/Goomba.h"
#include "Headers/FlyingKoopa.h"
#include "Headers/Koopa.h"

Bowser::Bowser()
{
    walkSpeed = 20.f;   

    isAlive = true;
    setHealth(50);

    currentAction = "WALK-";
    isAnimationInProgress = false;

    if (!entityTexture.loadFromFile("Source/Resources/texture/Enemies.png")) {
        throw std::runtime_error("Failed to load Koopa texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(4.0f, 4.0f);


    this->animationComponent = new AnimationComponent(this->entitySprite);
    initAnimations();

    movementComponent = new MovementComponent(walkSpeed, 3.0f);

    hitbox.setSize(sf::Vector2f(128.f, 140.f));
    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Green);
    hitbox.setOutlineThickness(-1.f);
    skill = random(1, 2);

    // shooting
    reloadTimer = 0;
}

Bowser::Bowser(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max): Bowser()
{
    this->position = position;
    this->size = size;
    this->x_min = x_min;
    this->x_max = x_max;
    setMoveRight(true);
}

Bowser::~Bowser()
{
}

void Bowser::initAnimations() {
    spritesSheet = {
        { "WALK-1", sf::IntRect(1, 186, 32, 35) },
        { "WALK-2", sf::IntRect(34, 186, 32, 35) },
        { "WALK-3", sf::IntRect(67, 186, 32, 35) },
		{ "FIRE-1", sf::IntRect(100, 186, 32, 35) },
		{ "FIRE-2", sf::IntRect(133, 186, 32, 35) },
		{ "FIRE-3", sf::IntRect(166, 186, 32, 35)},
		{ "FIRE-4", sf::IntRect(199, 186, 32, 35) },

		{ "WALKR-1", sf::IntRect(795, 186, 32, 35) },
		{ "WALKR-2", sf::IntRect(762, 186, 32, 35) },
		{ "WALKR-3", sf::IntRect(729, 186, 32, 35) },
		{ "FIRER-1", sf::IntRect(696, 186, 32, 35) },
		{ "FIRER-2", sf::IntRect(663, 186, 32, 35) },
		{ "FIRER-3", sf::IntRect(630, 186, 32, 35) },
		{ "FIRER-4", sf::IntRect(597, 186, 32, 35) }
    };
}

void Bowser::updateShooting(const float& dt) {
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
        sf::Vector2f bulletVelocity = sf::Vector2f(direction.x * 500.f, direction.y * 500.f);
        eventMediator->spawnPowerUp(new Bullet(this->getCenter(), sf::Vector2f(64, 64),
            "bullet","enemy", bulletVelocity));
    }
}

void Bowser::update(const float& dt) {
    updateAnimation(dt);
	if (skillDuration <= skillTimer) {
        updateVelocity(dt);
        eventMediator->applyExternalForce(this, dt);
        if (AnimationTimer <= animationtime)
        {
			AnimationTimer += dt;
        }
        else
        {
            skill = random(1, 2);
			skillTimer = 0;
			AnimationTimer = 0;
			if (skill == 1)
			{
				updateSkill_1(dt);
			}
            else if (skill == 2)
            {
                updateSkill_2(dt);
            }
            
        }
	}
	else {
		skillTimer += dt;
        updateVelocity(dt);
        updateShooting(dt);
        eventMediator->applyExternalForce(this, dt);
        move(dt);
	}
}

void Bowser::updateAnimation(const float& dt) {
    if (skillDuration <= skillTimer)
    {
		//std::cerr << "Bowser skill" << std::endl;
        if (this->isMoveLeft()) {
            animationComponent->setAnimationEnemies("FIRER-", spritesSheet, 0.2f);
        }
        else if (this->isMoveRight()) {
            animationComponent->setAnimationEnemies("FIRE-", spritesSheet, 0.2f);
        }
    }
    else
    {
        if (this->isMoveLeft()) {
            animationComponent->setAnimationEnemies("WALKR-", spritesSheet, 0.2f);
        }
        else if (this->isMoveRight()) {
            animationComponent->setAnimationEnemies("WALK-", spritesSheet, 0.2f);
        }
    }

    animationComponent->update(dt);
}

void Bowser::updateSkill_1(const float& dt) {

}

void Bowser::updateSkill_2(const float& dt) {
	//std::cerr << "Bowser skill 2" << std::endl;
    eventMediator->spawnEnemy(new Goomba(sf::Vector2f(374, 768.f), sf::Vector2f(64, 64), 310, 1184));
	eventMediator->spawnEnemy(new FlyingKoopa(sf::Vector2f(374, 600), sf::Vector2f(64, 64), 310, 1184));

	eventMediator->spawnEnemy(new Koopa(sf::Vector2f(1184, 768.f), sf::Vector2f(64, 64), 310, 1184));
	eventMediator->spawnEnemy(new FlyingKoopa(sf::Vector2f(1184, 600), sf::Vector2f(64, 64), 310, 1184));

	eventMediator->spawnEnemy(new Goomba(sf::Vector2f(700.f, 768.f), sf::Vector2f(64, 64), 310, 1184));
	//eventMediator->spawnEnemy(new FlyingKoopa(sf::Vector2f(700.f, 1000.f), sf::Vector2f(64, 64), 310, 1184));
}

void Bowser::getDamaged() {
}

void Bowser::move(const float& dt) {
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

bool Bowser::getIsAlive() const {
    return isAlive;
}

void Bowser::setIsAlive(bool alive) {
    isAlive = alive;
}

void Bowser::reactToPlayerCollision(int collidedSide) {
}

void Bowser::reactToBlockCollision(int collidedSide) {
}

