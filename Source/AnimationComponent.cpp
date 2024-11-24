#include "Headers/AnimationComponent.h"

AnimationComponent::AnimationComponent(sf::Sprite& sprite)
    : sprite(sprite), currentFrameIndex(0), animationSpeed(0.1f), elapsedTime(0) {}


void AnimationComponent::setAnimation(const std::string& animationName, const std::unordered_map<std::string, sf::IntRect>& spritesSheet, float speed, bool is_big) {
    if (currentAnimationName == animationName) {
        //std::cout << "Animation already set: " << animationName << std::endl;
        return;
    }

    currentAnimationFrames.clear();
    currentAnimationName = animationName;
    currentFrameIndex = 0;

    std::string prefix = is_big ? "isBig_" : "";

    for (const auto& pair : spritesSheet) {
        if (pair.first.find(animationName) == 0) {
            currentAnimationFrames.push_back(pair.second);
        }
    }

    
    animationSpeed =speed;

    elapsedTime = 0.0f;

    if (!currentAnimationFrames.empty()) {
        sprite.setTextureRect(currentAnimationFrames[0]);
    }
    /*
    else {
        std::cerr << "Animation '" << animationName << "' not found or empty in spritesSheet!" << std::endl;
    }*/
}


void AnimationComponent::update(float deltaTime) {
    /*
    /if (currentAnimationFrames.empty()) {
        return;
    }
    */

    elapsedTime += deltaTime;

    if (elapsedTime >= animationSpeed) {
        elapsedTime -= animationSpeed;

        currentFrameIndex = (currentFrameIndex + 1) % currentAnimationFrames.size();

        sprite.setTextureRect(currentAnimationFrames[currentFrameIndex]);
    }
}








