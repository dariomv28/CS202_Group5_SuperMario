#include "Headers/Mario.h"
#include "Headers/PhysicsEngine.h"

Mario::Mario(sf::Vector2f position, sf::Vector2f size,
    int health, int speed, PhysicsEngine* physicEngine) :
    PlayerManager(position, size, health, speed, physicEngine), is_big(false), currentAction("IDLE") {
    animationComponent = nullptr;
    movementComponent = new MovementComponent(1000, 500);
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

    if (!entityTexture.loadFromFile("Source/Resources/texture/Mario_Luigi.png")) {
        throw std::runtime_error("Failed to load Mario texture!");
    }

    // Set up sprite
    entitySprite.setTexture(entityTexture);
    entitySprite.setTextureRect(sf::IntRect(1, 17, 16, 16));

    // Set the origin to the center of the sprite for proper flipping
    entitySprite.setOrigin(8.0f, 8.0f);  
    entitySprite.setScale(4.0f, 4.0f);

    // Create animation component
    this->animationComponent = new AnimationComponent(this->entitySprite, this->entityTexture);
    initAnimations();

    // Set up hitbox
    hitbox.setSize(sf::Vector2f(64.f, 64.f));
    hitbox.setOrigin(32.f, 32.f);  // Half of 64x64
    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(1.f);
}

void Mario::initAnimations() {
    /*this->animationComponent->addAnimation("IDLE", 0.f, 1, 17, 1, 17, 64, 64);*/
}

// Movement and Action Functions

void Mario::setBig(bool big) {
    is_big = big;
}

bool Mario::isBig() const {
    return is_big;
}

void Mario::update(const float& dt) {
    handleInput(dt);
    move(dt);
    PlayerManager::update(dt);
    updateState();

    if (animationComponent) {
        updateAnimation(dt);
    }
}

void Mario::render(sf::RenderTarget* target) {
    if (target) {
        if (entitySprite.getTexture()) {
            /*std::cout << "Texture size: " << entitySprite.getTexture()->getSize().x << "x"
                << entitySprite.getTexture()->getSize().y << std::endl;*/
            target->draw(entitySprite);
            target->draw(hitbox);
        }
        else {
            std::cerr << "No texture loaded!" << std::endl;
        }
    }
    else {
        std::cerr << "Error: Mario::render() target is nullptr" << std::endl;
    }
}

void Mario::updateAnimation(const float& dt) {
    if (movementComponent->isMoveRight) {
        currentAction = "WALK_RIGHT";
        animationComponent->play("WALK_RIGHT", dt);
    }
    else if (movementComponent->isMoveLeft) {
        currentAction = "WALK_LEFT";
        animationComponent->play("WALK_LEFT", dt);
    }
    else if (movementComponent->isJump) {
        animationComponent->play("JUMP", dt);
    }
    else {
        currentAction = "IDLE";
        animationComponent->play("IDLE", dt);
    }
}

void Mario::updateState() {

}

void Mario::handleInput(const float& dt) {
    movementComponent->isMoveLeft = false;
    movementComponent->isMoveRight = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movementComponent->isMoveLeft = true;
        movementComponent->moveLeft(dt);

        entitySprite.setScale(-4.0f, 4.0f);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movementComponent->isMoveRight = true;
        movementComponent->moveRight(dt);
        entitySprite.setScale(4.0f, 4.0f);
    }

    // Handle jumping
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        movementComponent->isJump = true;
    }

    movementComponent->jump(dt);
    movementComponent->idle(dt);
}


void Mario::move(const float& dt) {
    if (movementComponent) {
        position.x += movementComponent->velocity.x * dt;
        position.y += movementComponent->velocity.y * dt;

        std::cout << movementComponent->velocity.x << " " << position.x << "\n";

        entitySprite.setPosition(position);

        if (position.y > 500.0f) {
            position.y = 500.0f;
            movementComponent->velocity.y = 0.0f;
            movementComponent->onGround = true;
        }

        hitbox.setPosition(position);
    }
}
