#pragma once
#include "Enemy.h"

class Heriss : public Enemy {
private:
    // Movement and positioning
    float walkSpeed;
    float x_min;
    float x_max;

    bool isAlive;
    float disappearDelay = 0.0f;

    // Animation sprite sheet
    std::unordered_map<std::string, sf::IntRect> spritesSheet;

    // Current action string
    std::string currentAction;
    bool isAnimationInProgress;

    void initAnimations();

public:
    Heriss();
    Heriss(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max);

    void updateAnimation(const float& dt) override;

    // State getters and setters
    bool getIsAlive() const;
    void setIsAlive(bool alive);

    // Update function
    void update(const float& dt) override;
    void getDamaged() override;

    // Collision response
    void move(const float& dt) override;
    void reactToPlayerCollision(int collidedSide) override;
    void reactToBlockCollision(int collidedSide) override;
};
