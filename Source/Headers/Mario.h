#ifndef MARIO_H
#define MARIO_H

#include "Headers/PlayerManager.h"
#include "Headers/AnimationComponent.h"
#include <SFML/Graphics.hpp>
#include <string>

class Mario : public PlayerManager {
public:
    Mario();
    ~Mario();

    void init();
    void initAnimations();
    void update(float deltaTime);

    void walkLeft();
    void walkRight();
    void jump();

    void setBig(bool big);
    bool isBig() const;

private:
    std::string m_name;
    sf::Sprite marioSprite;
    sf::Texture marioTexture;
    AnimationComponent* animationComponent;

    bool is_big;
    std::string currentAction;
};

#endif
