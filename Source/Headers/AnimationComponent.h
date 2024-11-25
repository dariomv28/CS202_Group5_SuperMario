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
    size_t currentFrameIndex;
    float animationSpeed;
    float elapsedTime;
    std::string currentAnimationName;

public:
    AnimationComponent(sf::Sprite& sprite);

    void setAnimation(const std::string& animationName, const std::unordered_map<std::string, sf::IntRect>& spritesSheet, float speed);

    void update(float deltaTime);
};

#endif // ANIMATIONCOMPONENT_H
