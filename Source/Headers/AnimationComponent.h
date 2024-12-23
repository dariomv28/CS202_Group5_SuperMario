#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "stdafx.h"


class AnimationComponent {
private:
    sf::Sprite& sprite;
    std::string currentAnimationName;

public:
    AnimationComponent(sf::Sprite& sprite);
    void setAnimation(const std::string& animationName, const std::unordered_map<std::string, sf::IntRect>& spritesSheet, float speed, bool is_big);
    void setAnimationEnemies(const std::string& animationName, const std::unordered_map<std::string, sf::IntRect>& spritesSheet, float speed);
    void update(float deltaTime);

    std::vector<sf::IntRect> currentAnimationFrames;
    size_t currentFrameIndex;
    float animationSpeed;
    float elapsedTime;

    bool isAnimationComplete();
};

#endif
