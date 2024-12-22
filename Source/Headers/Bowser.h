#pragma once
#include "Enemy.h"
class Bowser :
    public Enemy
{
private:
    const float reloadDuration = 7.5f;
    std::unordered_map<std::string, sf::IntRect> spritesSheet;

    void initAnimations();
public:
    Bowser();
	Bowser(sf::Vector2f position, sf::Vector2f size, float x_min = 32.0f, float x_max = 13416.0f);
	~Bowser();

    void updateAnimation(const float& dt) override;

    // Update function
    void update(const float& dt) override;
    void getDamaged() override;

    // Collision response
    void move(const float& dt) override;
    void reactToPlayerCollision(int collidedSide) override;
    void reactToBlockCollision(int collidedSide) override;
};

