#include "headers/Character.h"
#include <stdexcept>

PlayerManager* Character::createPlayer(const std::string& name, sf::Vector2f position, sf::Vector2f size, int health, int speed) {
    if (name == "Mario") {
        return new Mario(position, size, health, speed); // Cr�e un objet Mario
    }
    else if (name == "Luigi") {
        return new Luigi(position, size, health, speed); // Cr�e un objet Luigi
    }
    else {
        throw std::invalid_argument("Invalid character name: " + name); // Gestion des erreurs
    }
}
