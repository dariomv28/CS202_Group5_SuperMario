#include "Headers/Mario.h"
#include "Headers/PhysicsEngine.h"

Mario::Mario(sf::Vector2f position, sf::Vector2f size,
    int health, int speed, PhysicsEngine* physicEngine) :
    PlayerManager(position, size, health, speed, physicEngine), is_big(false), currentAction("IDLE") {
    animationComponent = nullptr;
    init();
}
Mario::Mario(): is_big(false), currentAction("IDLE") {
    animationComponent = nullptr;
}

Mario::~Mario() {
    
}

void Mario::init() {
    PlayerManager::init();
    m_name = "Mario";

    if (!entityTexture.loadFromFile(getImagePath())) {
        std::cerr << "Error loading Mario texture!" << std::endl;
    }
    else {
        entitySprite.setTexture(entityTexture);
        entitySprite.setPosition(400, 300);
    }

    
    this->animationComponent = new AnimationComponent(this->entitySprite, this->entityTexture);
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

void Mario::setBig(bool big) {
    is_big = big;
}


bool Mario::isBig() const {
    return is_big;
}

void Mario::update(const float& dt) {
    this->physicsEngine->playerUpdatePhysics(dt);
    this->updateVelocity(dt);
    this->move();
}

void Mario::render(sf::RenderTarget* target) {
	if (target) {
       // sf::RectangleShape rect(sf::Vector2f(64, 64));
       // rect.setPosition(this->getPosition());
       // rect.setFillColor(sf::Color::Red);
       // rect.setOutlineColor(sf::Color::Red);
		target->draw(entitySprite);
    }
    else {
        std::cerr << "Error: Mario::render() target is nullptr" << std::endl;
    }
}
