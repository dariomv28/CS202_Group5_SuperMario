#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>
#include <vector>

class AnimationComponent {
private:
    sf::Sprite& sprite;
    std::vector<sf::IntRect> currentAnimationFrames;
    std::string currentAnimationName;
    size_t currentFrameIndex;
    float animationSpeed;
    float elapsedTime;

public:
    AnimationComponent(sf::Sprite& sprite);
    void setAnimation(const std::string& animationName, const std::unordered_map<std::string, sf::IntRect>& spritesSheet, float speed, bool is_big);
    void update(float deltaTime);
};

#endif
