#include "Headers/Mario.h"
#include <iostream>

Mario::Mario() : is_big(false), animationComponent(nullptr), currentAction("IDLE") {}

Mario::~Mario() {
    delete animationComponent;
}

void Mario::init() {
    PlayerManager::init();
    m_name = "Mario";

    if (!marioTexture.loadFromFile(getImagePath())) {
        std::cerr << "Error loading Mario texture!" << std::endl;
    }
    else {
        marioSprite.setTexture(marioTexture);
        marioSprite.setPosition(400, 300);
    }

    
    this->animationComponent = new AnimationComponent(this->marioSprite, this->marioTexture);
    initAnimations();
}

void Mario::initAnimations() {
    // Define animations : not define actually I will modify
    this->animationComponent->addAnimation("IDLE", 15.f, 0, 0, 8, 0, 64, 64);
    this->animationComponent->addAnimation("WALK_DOWN", 11.f, 0, 1, 3, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_LEFT", 11.f, 4, 1, 7, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_RIGHT", 11.f, 8, 1, 11, 1, 64, 64);
    this->animationComponent->addAnimation("WALK_UP", 11.f, 12, 1, 15, 1, 64, 64);
    this->animationComponent->addAnimation("ATTACK", 5.f, 0, 2, 1, 2, 64, 64);
}

// Movement and Action Functions

void Mario::walkLeft() {
    currentAction = "WALK_LEFT";
    marioSprite.move(-5.0f, 0.0f);
}

void Mario::walkRight() {
    currentAction = "WALK_RIGHT";
    marioSprite.move(5.0f, 0.0f);
}

void Mario::jump() {
    currentAction = "JUMP";
    marioSprite.move(0.0f, -10.0f);
}


void Mario::update(float deltaTime) {
    if (currentAction == "WALK_LEFT") {
        animationComponent->play("WALK_LEFT", deltaTime);
    }
    else if (currentAction == "WALK_RIGHT") {
        animationComponent->play("WALK_RIGHT", deltaTime);
    }
    else if (currentAction == "JUMP") {
        animationComponent->play("JUMP", deltaTime);
    }
    else {
        animationComponent->play("IDLE", deltaTime);
    }
}


void Mario::setBig(bool big) {
    is_big = big;
}


bool Mario::isBig() const {
    return is_big;
}
