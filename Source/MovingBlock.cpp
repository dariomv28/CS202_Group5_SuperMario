#include "Headers/MovingBlock.h"

MovingBlock::MovingBlock() : SolidBlock() {
    this->moveSpeed = 100.f;
    this->moveDistance = 100.f;
    this->currentDirection = 0;
}

MovingBlock::MovingBlock(sf::Vector2f position, sf::Vector2f size, std::string name, float moveSpeed, float moveDistance)
    : SolidBlock(position, size, name)
{
    this->moveSpeed = moveSpeed;
    this->moveDistance = moveDistance;
    this->initialPosition = position;
    this->currentDirection = 0;
}

MovingBlock::~MovingBlock() {
}

void MovingBlock::updateMovement(const float& dt) {
    sf::Vector2f movement(0.f, 0.f);

    // Calculate relative position from initial position
    float dx = entitySprite.getPosition().x - initialPosition.x;
    float dy = entitySprite.getPosition().y - initialPosition.y;

    // Determine movement based on current direction
    switch (currentDirection) {
    case 0: // Moving right
        if (dx < moveDistance)
            movement.x = moveSpeed * dt;
        else
            currentDirection = 1;
        break;

    case 1: // Moving down
        if (dy < moveDistance)
            movement.y = moveSpeed * dt;
        else
            currentDirection = 2;
        break;

    case 2: // Moving left
        if (dx > 0)
            movement.x = -moveSpeed * dt;
        else
            currentDirection = 3;
        break;

    case 3: // Moving up
        if (dy > 0)
            movement.y = -moveSpeed * dt;
        else
            currentDirection = 0;
        break;
    }

    // Update positions
    entitySprite.move(movement);
    hitbox.move(movement);
}

void MovingBlock::update(const float& dt) {
    SolidBlock::update(dt);
    updateMovement(dt);
}

void MovingBlock::render(sf::RenderTarget* target) {
    SolidBlock::render(target);
}