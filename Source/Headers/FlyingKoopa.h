#pragma once
#include "Enemy.h"
class FlyingKoopa :
    public Enemy
{
private:
    // Movement and positioning
  //  float walkSpeed;
    float x_min;
    float x_max;

    bool isAlive;
  //  bool isShelled;
  //  float shellTimer;
  //  float disappearDelay = 0.0f;

    // Animation sprite sheet
    std::unordered_map<std::string, sf::IntRect> spritesSheet;

    // Current action string
 //   std::string currentAction;
 //   bool isAnimationInProgress;

    // Initialization
    virtual void initAnimations();
public:
    FlyingKoopa();
    FlyingKoopa(sf::Vector2f position, sf::Vector2f size, float x_min = 32.0f, float x_max = 13416.0f);

    void updateAnimation(const float& dt) override;

    // State getters and setters
    bool getIsAlive() const;
    void setIsAlive(bool alive);
    //bool getIsShelled() const;
   // void setIsShelled(bool shelled);

    // Update function
    void update(const float& dt) override;
    void getDamaged() override;

    // Collision response
    void move(const float& dt) override;
    void reactToPlayerCollision(int collidedSide) override;
    void reactToBlockCollision(int collidedSide) override;
};

