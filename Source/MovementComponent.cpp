#include "Headers/MovementComponent.h"

MovementComponent::MovementComponent() {
    acceleration = 500.f;
    maxVelocity = 1000.0f;
    isMoveLeft = false;
    isMoveRight = false;
    isJump = false;
    onGround = true;       
    hitCeiling = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    jumpsRemaining = MAX_JUMPS;  // Initialize jumps
    //eventMediator = new GameEventMediator();
}

MovementComponent::MovementComponent(float a, float maxV) {
    acceleration = static_cast<float>(a * 100);
    maxVelocity = static_cast<float>(maxV * 100);
    isMoveLeft = false;
    isMoveRight = false;
    isJump = false;
    onGround = true;
    hitCeiling = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
    jumpsRemaining = MAX_JUMPS;  // Initialize jumps
    //eventMediator = new GameEventMediator();
}

MovementComponent::~MovementComponent() {}

void MovementComponent::resetJumps() {
    jumpsRemaining = MAX_JUMPS;
}

int MovementComponent::getJumpsRemaining() const {
    return jumpsRemaining;
}

void MovementComponent::moveLeft(const float& dt) {
    if (!isMoveLeft) return;

    velocity.x -= acceleration * dt;

    if (velocity.x < -maxVelocity) {
        velocity.x = -maxVelocity;
    }
}

void MovementComponent::moveRight(const float& dt) {
    if (!isMoveRight) return;

    velocity.x += acceleration * dt;

    if (velocity.x > maxVelocity) {
        velocity.x = maxVelocity;
    }
}
void MovementComponent::setmoveLeft(bool moveLeft) {
	isMoveLeft = moveLeft;
}

void MovementComponent::setmoveRight(bool moveRight) {
	isMoveRight = moveRight;
}
void MovementComponent::jump(const float& dt, GameEventMediator* eventMediator) {
    
    if (onGround && isJump) {
        velocity.y = -700.f;
        onGround = false;
        isJump = false;
        jumpsRemaining = MAX_JUMPS - 1; 
    }
    else if (!onGround && isJump && jumpsRemaining > 0) {
        velocity.y = -700.f;
        isJump = false;
        jumpsRemaining--;
    }
    //eventMediator->playJumpSound();
}

