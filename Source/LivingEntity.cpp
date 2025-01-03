#include "Headers/LivingEntity.h"
#include "Headers/GameEventMediator.h"

LivingEntity::LivingEntity()
{
}

LivingEntity::LivingEntity(sf::Vector2f position, sf::Vector2f size, int health, int speed):
	GameObject(position, size)
{
	this->health = health;
	this->speed = speed;
	this->movementComponent = new MovementComponent(speed, 5.0f);
	this->movementComponent->onGround = false;
	//this->movementComponent->setEventMediator(eventMediator);
	//this->animationComponent = new AnimationComponent();
}


LivingEntity::~LivingEntity()
{
	delete animationComponent;
	delete movementComponent;
}

void LivingEntity::setHealth(int health)
{
	this->health = health;
}

int LivingEntity::getHealth() const
{
	return health;
}

void LivingEntity::setSpeed(int speed)
{
	this->speed = speed;
}

int LivingEntity::getSpeed() const
{
	return speed;
}


void LivingEntity::setOnGround(bool onGround)
{
	this->movementComponent->onGround = onGround;
}

bool LivingEntity::getOnGround() const
{
	return this->movementComponent->onGround;
}

void LivingEntity::setHitCeiling(bool hitCeiling)
{
	this->movementComponent->hitCeiling = hitCeiling;
}

bool LivingEntity::getHitCeiling() const
{
	return this->movementComponent->hitCeiling;
}

void LivingEntity::setVelocity(sf::Vector2f velocity)
{
	this->movementComponent->velocity = velocity;
}

sf::Vector2f LivingEntity::getVelocity() const
{
	return this->movementComponent->velocity;
}

bool LivingEntity::isMoveLeft() const
{
	return this->movementComponent->isMoveLeft;
}

void LivingEntity::setMoveLeft(bool moveLeft)
{
	this->movementComponent->isMoveLeft = moveLeft;
}

bool LivingEntity::isMoveRight() const
{
	return this->movementComponent->isMoveRight;
}

void LivingEntity::setMoveRight(bool moveRight)
{
	this->movementComponent->isMoveRight = moveRight;
}

bool LivingEntity::isJump() const
{
	return this->movementComponent->isJump;
}

void LivingEntity::setJump(bool jump)
{
	this->movementComponent->isJump = jump;
}

void LivingEntity::updateVelocity(const float& dt)
{
	this->movementComponent->moveLeft(dt);
	this->movementComponent->moveRight(dt);
	this->movementComponent->jump(dt, eventMediator);
}

void LivingEntity::move(const float& dt)
{
	//std::cout << position.x << " " << position.y << std::endl;
	this->position += this->movementComponent->velocity * dt;

	//std::cout << position.x << " " << position.y << std::endl;
	this->position.x = std::max<float>(this->position.x, 32.0);
	this->position.x = std::min<float>(this->position.x, 13416);
	this->entitySprite.setPosition(this->position);
	this->hitbox.setPosition(this->position);
}

void LivingEntity::update(const float& dt) {
	updateVelocity(dt);
}

void LivingEntity::render(sf::RenderTarget* target) {
	if (target) {
		target->draw(entitySprite);
	}
}