#include "Headers/LivingEntity.h"
#include "Headers/PhysicsEngine.h"

LivingEntity::LivingEntity()
{
	this->health = 0;
	this->speed = 0;
	this->movementComponent = new MovementComponent(2, speed);
	//this->animationComponent = new AnimationComponent();
}

LivingEntity::LivingEntity(sf::Vector2f position, sf::Vector2f size, int health, int speed, PhysicsEngine* physicEngine):
	GameObject(position, size, physicEngine)
{
	this->health = health;
	this->speed = speed;
	this->movementComponent = new MovementComponent();
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
	this->movementComponent->jump(dt);
}

void LivingEntity::move(const float& dt)
{
	//std::cout << "Moved " << this->getVelocity().x << ' ' << this->getVelocity().y << '\n';
	this->position += this->movementComponent->velocity;
	this->position.x = std::max<float>(this->position.x, 32.0);
	this->position.x = std::min<float>(this->position.x, 13416);

	std::cout << position.x << "\n";
	this->entitySprite.setPosition(this->position);
	this->hitbox.setPosition(this->position);
}

void LivingEntity::update(const float& dt) {
	updateVelocity(dt);

	// Update animation if it exists
	//if (animationComponent) {
		// Update animation based on current state
	//	updateAnimation(dt);
	//}
}

void LivingEntity::render(sf::RenderTarget* target) {
	if (target) {
		target->draw(entitySprite);
	}
}