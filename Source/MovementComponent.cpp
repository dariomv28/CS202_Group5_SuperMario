#include "Headers/MovementComponent.h"

MovementComponent::MovementComponent() {
    acceleration = 1000.0f;
    maxVelocity = 500.0f;
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
    velocity.x -= acceleration * dt;
    if (velocity.x < -maxVelocity) {
        velocity.x = -maxVelocity;
    }

}

void MovementComponent::moveRight(const float& dt) {
    velocity.x += acceleration * dt;
    if (velocity.x > maxVelocity) {
        velocity.x = maxVelocity;
    }

}

void MovementComponent::jump(const float& dt) {
    if (onGround && isJump) {
        velocity.y = -1.0f;  // Negative velocity for upward movement
        onGround = false;
        isJump = false;       // Reset jump flag
    }
}

void MovementComponent::idle(const float& dt) {
    // Apply friction/deceleration
    const float friction = 0.f;

    if (!isMoveLeft && !isMoveRight) {
        if (velocity.x > 0) {
            velocity.x = std::max(0.0f, velocity.x - friction * dt);
        }
        else if (velocity.x < 0) {
            velocity.x = std::min(0.0f, velocity.x + friction * dt);
        }
    }

    if (!onGround) {
        velocity.y += 1500.0f * dt; 
    }

    if (velocity.y > 1000.0f) {
        velocity.y = 1000.0f;
    }
}