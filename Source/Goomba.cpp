#include "Headers/Goomba.h"
#include "Headers/GameEventMediator.h"

Goomba::Goomba() : Enemy() {
	walkSpeed = 20.0f;

	isAlive = true;
	setHealth(1);

	currentAction = "WALK";
	isAnimationInProgress = false;
	
	if (!entityTexture.loadFromFile("Source/Resources/texture/Enemies.png")) {
		throw std::runtime_error("Failed to load Goomba texture!");
	}

	entitySprite.setTexture(entityTexture);
	entitySprite.setScale(4.0f, 4.0f);

	this->animationComponent = new AnimationComponent(this->entitySprite);
	initAnimations();

	movementComponent = new MovementComponent(walkSpeed, 3.0f);

	hitbox.setSize(sf::Vector2f(64.f, 64.f));
	hitbox.setPosition(position);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1.f);
}

Goomba::Goomba(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max) : Goomba() {
	this->position = position;
	this->size = size;
	this->x_min = x_min;
	this->x_max = x_max;
	setMoveRight(true);
}

void Goomba::initAnimations() {
	spritesSheet = {
		{ "WALK-1", sf::IntRect(1, 45, 16, 16) },
		{ "WALK-2", sf::IntRect(18, 45, 16, 16) },
		{ "SQUISH", sf::IntRect(35, 53, 16, 8) }
	};
}

void Goomba::move(const float& dt) 
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

	// std::cout << this->getVelocity().x << std::endl;
}

void Goomba::updateAnimation(const float& dt) {
	if (isAlive) {
		animationComponent->setAnimationEnemies("WALK-", spritesSheet, 0.2f);
		animationComponent->update(dt);
	}
	else {
		animationComponent->setAnimationEnemies("SQUISH", spritesSheet, 0.2f);
		animationComponent->update(dt);
	}
}

bool Goomba::getIsAlive() const{
	return isAlive;
}

void Goomba::setIsAlive(bool alive) {
	isAlive = alive;
}

void Goomba::update(const float& dt) {
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

void Goomba::reactToPlayerCollision(int collidedSide) {
	if (!isAlive) return;
	if (collidedSide == Collide_Top) {
		setIsAlive(false);
		eventMediator->increaseScore(300);
		this->hitbox.setSize(sf::Vector2f(64.f, 32.f));

		this->entitySprite.setPosition(this->position);
		this->hitbox.setPosition(this->position);
	}
	else {
		if (collidedSide == Collide_Left) eventMediator->pushPlayerLeft();
		else eventMediator->pushPlayerRight();
		eventMediator->decreasePlayerHealth();
	}
}

void Goomba::reactToBlockCollision(int collidedSide) {
	if (collidedSide == Collide_Left) {
		setMoveLeft(false);
		setMoveRight(true);
	}
	else if (collidedSide == Collide_Right) {
		setMoveRight(false);
		setMoveLeft(true);
	}
}

void Goomba::setScaleSprite(std::string name) {

}