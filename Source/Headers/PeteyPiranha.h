#pragma once
#include "Enemy.h"
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class PeteyPiranha : public Enemy {
private:

    bool isAlive;
    bool isMouthOpen;


    float mouthTimer;
    float switchInterval;


    std::unordered_map<std::string, sf::IntRect> spritesSheet;

    bool hasDamagedPlayer;


    sf::IntRect mouthOpenSprite;
    sf::IntRect mouthClosedSprite;

    void initSprites();

public:

    PeteyPiranha();
    PeteyPiranha(sf::Vector2f position, sf::Vector2f size);


    bool getIsAlive() const override;
    void setIsAlive(bool alive) override;

    void getDamaged() override;
    void reactToPlayerCollision(int collidedSide) override;
    void reactToBlockCollision(int collidedSide) override;


    void update(const float& dt) override;
    void updateAnimation(const float& dt) override;
};
