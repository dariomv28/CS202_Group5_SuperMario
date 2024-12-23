#pragma once

#include "PlayerManager.h" 
#include "AnimationComponent.h"

class Luigi : public PlayerManager {
public:
    Luigi();
    Luigi(sf::Vector2f position, sf::Vector2f size, int health = 3, int speed = 15.0f);
    ~Luigi();

    // Initialization function
    void init();
    void initAnimations();
};
