#pragma once
#include "Enemy.h"
class FlyingKoopa :
    public Enemy
{
private:
    // Movement and positioning
    float walkSpeed;
    float x_min;
    float x_max;

    bool isAlive;

    float disappearDelay = 0.0f;
    float reloadTimer = 0.0f;
	const float reloadFire = 5.0f;

    std::unordered_map<std::string, sf::IntRect> spritesSheet;

    virtual void initAnimations();
public:
    FlyingKoopa();
    FlyingKoopa(sf::Vector2f position, sf::Vector2f size);
    FlyingKoopa(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max);

    void updateAnimation(const float& dt) override;

    // State getters and setters
    bool getIsAlive() const;
    void setIsAlive(bool alive);
    //bool getIsShelled() const;
   // void setIsShelled(bool shelled);

    // Update function
    void updateShooting(const float& dt);
    void update(const float& dt) override;
    void getDamaged() override;

    // Collision response
    void move(const float& dt) override;
    void reactToPlayerCollision(int collidedSide) override;
    void reactToBlockCollision(int collidedSide) override;
};

