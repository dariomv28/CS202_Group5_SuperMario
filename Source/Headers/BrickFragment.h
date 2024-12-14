#pragma once
#include "stdafx.h"

class BrickFragment {
public:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    float rotation;
    float rotationSpeed;

    BrickFragment(const sf::Texture& texture, sf::IntRect textureRect, sf::Vector2f position);
    void update(float dt);
};