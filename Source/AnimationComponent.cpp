#include "Headers/AnimationComponent.h"


AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
    : sprite(sprite), textureSheet(texture_sheet) {}

AnimationComponent::~AnimationComponent() {
    for (auto& anim : this->animations)
        delete anim.second;
}


AnimationComponent::Animation::Animation(sf::Sprite& sprite, sf::Texture& texture_sheet, float animation_timer,
    int startX, int startY, int framesX, int framesY, int width, int height)
    : sprite(sprite), textureSheet(texture_sheet), animationTimer(animation_timer), timer(0.f), width(width), height(height), currentFrame(0) {
    for (int x = startX; x <= framesX; ++x) {
        frames.push_back(sf::IntRect(x * width, startY * height, width, height));
    }
    sprite.setTexture(texture_sheet);
    sprite.setTextureRect(frames[0]);
}

void AnimationComponent::Animation::play(const float& dt) {
    timer += dt;
    if (timer >= animationTimer) {
        timer = 0.f;
        currentFrame = (currentFrame + 1) % frames.size();
        sprite.setTextureRect(frames[currentFrame]);
    }
}

void AnimationComponent::Animation::reset() {
    timer = 0.f;
    currentFrame = 0;
}


void AnimationComponent::addAnimation(const std::string& key, float animation_timer, int startX, int startY, int framesX, int framesY, int width, int height) {
    this->animations[key] = new Animation(this->sprite, this->textureSheet, animation_timer, startX, startY, framesX, framesY, width, height);
}


void AnimationComponent::play(const std::string& key, const float& dt) {
    if (this->animations.count(key))
        this->animations[key]->play(dt);
}
