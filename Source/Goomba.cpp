#include "Headers/Goomba.h"

Goomba::Goomba() : Enemy() {
	walkSpeed = 30.0f;

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

	movementComponent = new MovementComponent(walkSpeed, 5.0f);

	hitbox.setSize(sf::Vector2f(64.f, 64.f));
	hitbox.setPosition(position);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.f);
}

Goomba::Goomba(sf::Vector2f position, sf::Vector2f size) : Goomba() {
	this->position = position;
	this->size = size;
	setMoveLeft(true);
}

void Goomba::initAnimations() {
	spritesSheet = {
		{ "WALK-1", sf::IntRect(1, 45, 16, 16) },
		{ "WALK-2", sf::IntRect(18, 45, 16, 16) },
		{ "SQUISH", sf::IntRect(35, 53, 8, 16) }
	};
}

void Goomba::moveWithView(const float& dt, const sf::View& view)
{
	float leftMostX = view.getCenter().x - (view.getSize().x / 2.0f);
	float rightMostX = view.getCenter().x + (view.getSize().x / 2.0f) - 20.0f;

	this->position += this->movementComponent->velocity;
	this->position.x = std::max<float>(this->position.x, leftMostX);
	this->position.x = std::min<float>(this->position.x, rightMostX);
	this->entitySprite.setPosition(this->position);
	this->hitbox.setPosition(this->position);

	if (this->position.x == leftMostX) {
		setMoveLeft(false);
		setMoveRight(true);
	}
	else if (this->position.x == rightMostX) {
		setMoveLeft(true);
		setMoveRight(false);
	}
}

void Goomba::update(const float& dt) {
	if (!isAlive) return;
	updateVelocity(dt);
	updateAnimation(dt);
	move(dt);

	if (position.x <= 32.0f) {
		setMoveLeft(false);
		setMoveRight(true);
	}
	else if (position.x >= 800.0f) {  
		setMoveLeft(true);
		setMoveRight(false);
	}
}

void Goomba::updateAnimation(const float& dt) {
	if (isAlive) {
		animationComponent->setAnimationEnemies("WALK-", spritesSheet, 0.2f);
		animationComponent->update(dt);
	}
	else {
		animationComponent->setAnimationEnemies("SQUISH", spritesSheet, 0.2f);
	}
}

bool Goomba::getIsAlive() const{
	return isAlive;
}

void Goomba::setIsAlive(bool alive) {
	isAlive = alive;
}

