#include "Headers/Mario.h"
#include "Headers/PhysicsEngine.h"
#include <stdexcept>

Mario::Mario(sf::Vector2f position, sf::Vector2f size, int health, int speed, PhysicsEngine* physicEngine)
    : PlayerManager(position, size, health, speed, physicEngine), is_big(true), currentAction("IDLE"), isAnimationInProgress(false) {
    animationComponent = nullptr;
    movementComponent = new MovementComponent(100000, 3);
    init();
}

Mario::Mario() : is_big(true), currentAction("IDLE"), isAnimationInProgress(false) {
    animationComponent = nullptr;
}

Mario::~Mario() {
    delete animationComponent;
}

void Mario::init() {
    PlayerManager::init();
    m_name = "Mario";

    if (!entityTexture.loadFromFile("Source/Resources/texture/Mario_Luigi.png")) {
        throw std::runtime_error("Failed to load Mario texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setOrigin(8.0f, 8.0f);
    entitySprite.setScale(4.0f, 4.0f);

    animationComponent = new AnimationComponent(entitySprite);
    initAnimations();

    // Initialiser l'animation par défaut à "IDLE-"
    currentAction = "IDLE-";
    animationComponent->setAnimation("IDLE", spritesSheet, 0.2f);
}


void Mario::initAnimations() {
    spritesSheet = {
        { "IDLE", sf::IntRect(1, 0, 16, 32) },
        { "WALK-1", sf::IntRect(17, 0, 16, 32) },
        { "WALK-2", sf::IntRect(37, 0, 16, 32) },
        { "RUN-1", sf::IntRect(53, 0, 16, 32) },
        { "RUN-2", sf::IntRect(69, 0, 16, 32) },
        { "JUMP-1", sf::IntRect(86, 0, 16, 32) },
        { "JUMP-2", sf::IntRect(103, 0, 16, 32) },
        { "JUMP-3", sf::IntRect(120, 0, 16, 32) },
        { "JUMP-4", sf::IntRect(139, 0, 16, 32) },
        { "JUMP-5", sf::IntRect(156, 0, 16, 32) },
        { "VICTORY-1", sf::IntRect(171, 0, 16, 32) },
        { "VICTORY-2", sf::IntRect(189, 0, 16, 32) },
        { "VICTORY-3", sf::IntRect(205, 0, 16, 32) },
        { "BECOME_BIG", sf::IntRect(224, 0, 16, 32) },
        { "isBig_IDLE", sf::IntRect(241, 0, 16, 32) },
        { "isBig_WALK-1", sf::IntRect(256, 0, 16, 32) },
        { "isBig_WALK-2", sf::IntRect(273, 0, 16, 32) },
        { "isBig_RUN-1", sf::IntRect(290, 0, 16, 32) },
        { "isBig_RUN-2", sf::IntRect(307, 0, 16, 32) },
        { "isBig_JUMP-1", sf::IntRect(328, 0, 20, 32) },
        { "isBig_JUMP-2", sf::IntRect(354, 0, 16, 32) },
        { "isBig_JUMP-3", sf::IntRect(378, 0, 16, 32) },
        { "isBig_JUMP-4", sf::IntRect(401, 0, 16, 32) },
        { "isBig_JUMP-5", sf::IntRect(418, 0, 16, 32) },
        { "isBig_CROUCH", sf::IntRect(433, 0, 16, 32) },
        { "isBig_VICTORY-1", sf::IntRect(450, 0, 16, 32) },
        { "isBig_VICTORY-2", sf::IntRect(467, 0, 16, 32) },
        { "isBig_VICTORY-3", sf::IntRect(484, 0, 16, 32) },
        { "isBig_VICTORY-4", sf::IntRect(501, 0, 16, 32) },
    };
}

void Mario::update(const float& dt) {
    handleInput(dt);
    updateAnimation(dt);
    physicsEngine->playerUpdatePhysics(dt);
    updateVelocity(dt);
    move(dt);
}

void Mario::handleInput(const float& dt) {
    // Reset les mouvements et les actions
    movementComponent->isMoveLeft = false;
    movementComponent->isMoveRight = false;
    movementComponent->isJump = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        movementComponent->isMoveLeft = true;
        entitySprite.setScale(-4.0f, 4.0f); // Inverser l'échelle pour regarder à gauche
        currentAction = "WALK-";            // Animation WALK
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        movementComponent->isMoveRight = true;
        entitySprite.setScale(4.0f, 4.0f); // Échelle normale pour regarder à droite
        currentAction = "WALK-";            // Animation WALK
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        movementComponent->isJump = true;
        currentAction = "JUMP-";            // Animation JUMP
        isAnimationInProgress = true;      // Indique qu'une animation prioritaire est en cours
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        if(is_big){
            currentAction = "CROUCH";          // Animation CROUCH
            isAnimationInProgress = true;
        }
              // Indique qu'une animation prioritaire est en cours
    }
    else {
        currentAction = "IDLE";            // Animation IDLE si aucune touche n'est pressée
    }
}

void Mario::updateAnimation(const float& dt) {
    std::string prefix = is_big ? "isBig_" : "";
    bool animationSet = false; // Pour vérifier si une animation a été définie

    if (currentAction == "WALK-") {
        animationComponent->setAnimation(prefix + "WALK-", spritesSheet, 0.15f);
        animationSet = true;
    }
    else if (currentAction == "JUMP-") {
        animationComponent->setAnimation(prefix + "JUMP-", spritesSheet, 0.2f);
        animationSet = true;
    }
    else if (currentAction == "CROUCH") {
        animationComponent->setAnimation(prefix + "CROUCH", spritesSheet, 0.2f);
        animationSet = true;
    }

    // Si aucune animation n'est définie, jouer l'animation IDLE
    if (!animationSet) {
        animationComponent->setAnimation(prefix + "IDLE", spritesSheet, 0.2f);
    }

    // Toujours mettre à jour l'animation, même si la touche est maintenue
    animationComponent->update(dt);
}

void Mario::render(sf::RenderTarget* target) {
    if (target) {
        target->draw(entitySprite);
    }
    else {
        std::cerr << "Render target is null!" << std::endl;
    }
}

bool Mario::getIsBig() const {
    return is_big;
}
