#include "Headers/MovementComponent.h"

MovementComponent::MovementComponent() {
	acceleration = 2;
	maxVelocity = 10;
	isMoveLeft = false;
	isMoveRight = false;
	isJump = false;
	onGround = false;
	hitCeiling = false;
	velocity = sf::Vector2f(0, 0);

}

MovementComponent::MovementComponent(int a, int maxV) {
	acceleration = a;
	maxVelocity = maxV;
	isMoveLeft = false;
	isMoveRight = false;
	isJump = false;
	onGround = false;
	hitCeiling = false;
	velocity = sf::Vector2f(0, 0);

}

MovementComponent::~MovementComponent() {

}

void MovementComponent::moveLeft(const float& dt) {
	if (!isMoveLeft) return;
	velocity.x -= acceleration*dt;
	if (velocity.x < -maxVelocity) {
		velocity.x = -maxVelocity;
	}
}

void MovementComponent::moveRight(const float& dt) {
	if (!isMoveRight) return;
	velocity.x += acceleration*dt;
	if (velocity.x > maxVelocity) {
		velocity.x = maxVelocity;
	}
}

void MovementComponent::jump(const float& dt) {
	if (!onGround) {
		isJump = false;
	}
	if (!isJump) return;
	velocity.y -= maxVelocity;
}

void MovementComponent::idle(const float& dt) {
	if (isMoveLeft || isMoveRight) return;
	if (velocity.x > 0) {
		//Decelerate
		velocity.x -= acceleration*dt;
		if (velocity.x < 0) {
			velocity.x = 0;
		}
	}
	else if (velocity.x < 0) {
		velocity.x += acceleration*dt;
		if (velocity.x > 0) {
			velocity.x = 0;
		}
	}
}