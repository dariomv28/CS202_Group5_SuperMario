#include "Headers/MovementComponent.h"

MovementComponent::MovementComponent() {
    acceleration = 100000.0f;
    maxVelocity = 80000.0f;
    isMoveLeft = false;
    isMoveRight = false;
    isJump = false;
    onGround = true;       
    hitCeiling = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
}

MovementComponent::MovementComponent(int a, int maxV) {
    acceleration = static_cast<float>(a);
    maxVelocity = static_cast<float>(maxV);
    isMoveLeft = false;
    isMoveRight = false;
    isJump = false;
    onGround = true;
    hitCeiling = false;
    velocity = sf::Vector2f(0.0f, 0.0f);
}

MovementComponent::~MovementComponent() {
}

void MovementComponent::moveLeft(const float& dt) {
    if (!isMoveLeft) return;
    velocity.x -= acceleration * dt;
    if (velocity.x < -maxVelocity) {
        velocity.x = -maxVelocity;
    }
    isMoveLeft = false;
}

void MovementComponent::moveRight(const float& dt) {
    if (!isMoveRight) return;
    velocity.x += acceleration * dt;
    if (velocity.x > maxVelocity) {
        velocity.x = maxVelocity;
    }
    isMoveRight = false;
}

void MovementComponent::jump(const float& dt) {
    if (!onGround) isJump = false;
    if (onGround && isJump) {
        velocity.y = -2.5f;  // Negative velocity for upward movement
        onGround = false;
        isJump = false;       // Reset jump flag
    }
}
