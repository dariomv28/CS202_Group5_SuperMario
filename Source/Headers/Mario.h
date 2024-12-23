#pragma once

#include "PlayerManager.h" 
#include "AnimationComponent.h"

class Mario : public PlayerManager {
public:
    Mario();

    Mario(sf::Vector2f position, sf::Vector2f size, int health = 3, int speed = 15.0f);
    ~Mario();

    // Initialization function
    void init();
    void initAnimations();
};
