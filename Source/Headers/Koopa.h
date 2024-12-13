#pragma once
#include "Enemy.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class Koopa : public Enemy {
private:
    // Movement and positioning
    float walkSpeed;
    float x_min;
    float x_max;

    bool isAlive;
    bool isShelled;
    float shellTimer;
    float disappearDelay = 0.0f;

    // Animation sprite sheet
    std::unordered_map<std::string, sf::IntRect> spritesSheet;

    // Current action string
    std::string currentAction;
    bool isAnimationInProgress;

    // Initialization
    void initAnimations();

public:
    // Constructors
    Koopa();
    Koopa(sf::Vector2f position, sf::Vector2f size, float x_min = 32.0f, float x_max = 13416.0f);
    
    void updateAnimation(const float& dt) override;

    // State getters and setters
    bool getIsAlive() const;
    void setIsAlive(bool alive);
    bool getIsShelled() const;
	void setIsShelled(bool shelled);

    // Update function
    void update(const float& dt) override;

    // Collision response
    void move(const float& dt) override;
    void reactToPlayerCollision(int collidedSide) override;
    void setScaleSprite(std::string name) override;
};