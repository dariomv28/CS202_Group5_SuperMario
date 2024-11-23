//#pragma once
//
//#include "PlayerManager.h"
//#include "AnimationComponent.h"
//
//class PhysicsEngine;
//
//class Mario : public PlayerManager {
//private:
//    std::string m_name;
//    bool is_big;
//    std::string currentAction;
//    bool isAnimationInProgress;
//    std::unordered_map<std::string, sf::IntRect> spritesSheet;
//
//public:
//    Mario(sf::Vector2f position, sf::Vector2f size, int health, int speed, PhysicsEngine* physicEngine);
//    Mario();
//    ~Mario();
//
//    void init();
//    void initAnimations();
//
//    //void setBig(bool big);
//    bool getIsBig() const;
//
//    void update(const float& dt) override;
//    void render(sf::RenderTarget* target) override;
//    void handleInput(const float& dt);
//    void updateAnimation(const float& dt);
//};
#pragma once

#include "PlayerManager.h" // Ensure PlayerManager is included
#include "AnimationComponent.h"

//class PhysicsEngine;

class Mario : public PlayerManager {
private:
    std::string m_name;
    bool is_big;
    std::string currentAction;
    bool isAnimationInProgress;
    std::unordered_map<std::string, sf::IntRect> spritesSheet;

public:
    Mario(sf::Vector2f position, sf::Vector2f size, int health, int speed, PhysicsEngine* physicEngine);
    Mario();
    ~Mario();

    void init();
    void initAnimations();

    //void setBig(bool big);
    bool getIsBig() const;

    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
    void handleInput(const float& dt);
    void updateAnimation(const float& dt);
};
