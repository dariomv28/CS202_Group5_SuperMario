#pragma once
#include <string>
#include <SFML/System.hpp>
#include "PlayerManager.h"
#include "Mario.h"
#include "Luigi.h"

class Character {
public:
    static PlayerManager* createPlayer(const std::string& name, sf::Vector2f position, sf::Vector2f size, int health, int speed);
};