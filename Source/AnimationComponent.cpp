#include "Headers/AnimationComponent.h"
#include <iostream>

AnimationComponent::AnimationComponent(sf::Sprite& sprite)
    : sprite(sprite), currentFrameIndex(0), animationSpeed(0.1f), elapsedTime(0) {}


void AnimationComponent::setAnimation(const std::string& animationName, const std::unordered_map<std::string, sf::IntRect>& spritesSheet, float speed) {
    // Si l'animation demandée est déjà en cours, ne rien faire
    if (currentAnimationName == animationName) {
        return;
    }

    // Réinitialise l'animation actuelle
    currentAnimationFrames.clear();
    currentAnimationName = animationName;
    currentFrameIndex = 0;
    animationSpeed = speed;
    elapsedTime = 0.f;

    // Recherche toutes les frames correspondantes dans spritesSheet
    for (const auto& pair : spritesSheet) {
        if (pair.first.find(animationName) != std::string::npos) {
            currentAnimationFrames.push_back(pair.second);
        }
    }

    // Applique la première frame immédiatement
    if (!currentAnimationFrames.empty()) {
        sprite.setTextureRect(currentAnimationFrames[0]);
    }
    else {
        std::cerr << "Animation '" << animationName << "' not found in spritesSheet!" << std::endl;
    }
}



void AnimationComponent::update(float deltaTime) {
    if (currentAnimationFrames.empty())
        return;

    elapsedTime += deltaTime;
    if (elapsedTime >= animationSpeed) {
        elapsedTime = 0;

        currentFrameIndex = (currentFrameIndex + 1) % currentAnimationFrames.size();
        sprite.setTextureRect(currentAnimationFrames[currentFrameIndex]);
    }
}

