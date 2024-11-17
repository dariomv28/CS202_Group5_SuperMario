#pragma once
#include "PlayerManager.h"
#include "AnimationComponent.h"

class PhysicsEngine;

class Mario : public PlayerManager {
private:
    std::string m_name;
    bool is_big;
    std::string currentAction;
public:
    Mario(sf::Vector2f position, sf::Vector2f size, 
        int health, int speed, PhysicsEngine* physicEngine);
    Mario();
    ~Mario();

    void init();
    void initAnimations();

    void setBig(bool big);
    bool isBig() const;

    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
    void updateState();
    void updateAnimation(const float& dt);

    void handleInput(const float& dt);
    void move(const float& dt);
};
