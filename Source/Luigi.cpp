#include "Headers/Luigi.h"
#include "Headers/PhysicsEngine.h"
#include "Headers/FireBuff.h"
#include <stdexcept>

Luigi::Luigi() : PlayerManager(sf::Vector2f(0, 0), sf::Vector2f(CELL_SIZE, CELL_SIZE), 4, 30.f)
{
    animationComponent = nullptr;
    movementComponent = new MovementComponent(30.f, 4.0f, 1, -1400.f);
    init();
}

Luigi::Luigi(sf::Vector2f position, sf::Vector2f size, int health, int speed)
    : PlayerManager(position, size, health, speed) {
    animationComponent = nullptr;
    movementComponent = new MovementComponent(speed, 4.0f, 1, -1400.f);
    init();
}

Luigi::~Luigi() {
    delete animationComponent;
}

void Luigi::init() {
    PlayerManager::init();
    m_name = "Luigi";

    if (!entityTexture.loadFromFile("Source/Resources/texture/Mario_Luigi.png")) {
        throw std::runtime_error("Failed to load Luigi texture!");
    }

    entitySprite.setTexture(entityTexture);
    entitySprite.setScale(4.0f, 4.0f);

    this->animationComponent = new AnimationComponent(this->entitySprite);
    initAnimations();

    hitbox.setPosition(position);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(sf::Color::Red);
    hitbox.setOutlineThickness(-1.f);
    updateHitboxSize();

    currentAction = "IDLE-";
    isMovingLeft = false;  // Initialize direction
}

void Luigi::initAnimations() {
    // Right

    std::unordered_map<std::string, sf::IntRect> idle = {
        {"IDLE-", allSpritesLuigi["IDLE-"]},
    };

    std::unordered_map<std::string, sf::IntRect> walk1 = {
        {"WALK-1", allSpritesLuigi["WALK-1"]},
        {"WALK-2", allSpritesLuigi["WALK-2"]},
        {"WALK-3", allSpritesLuigi["WALK-1"]},
        {"WALK-4", allSpritesLuigi["IDLE-"]},
    };

    std::unordered_map<std::string, sf::IntRect> stop = {
        {"STOP-", allSpritesLuigi["STOP-"]},
    };

    std::unordered_map<std::string, sf::IntRect> run1 = {
        {"RUN-1", allSpritesLuigi["RUN-1"] },
        {"RUN-2", allSpritesLuigi["WALK-1"] },
        {"RUN-3", allSpritesLuigi["WALK-2"] },
        {"RUN-4", allSpritesLuigi["WALK-1"] },
        {"RUN-5", allSpritesLuigi["IDLE-"] },
    };

    std::unordered_map<std::string, sf::IntRect> jump = {
        {"JUMP-1", allSpritesLuigi["JUMP-1"]},
        {"JUMP-2", allSpritesLuigi["JUMP-2"]},
        {"JUMP-3", allSpritesLuigi["JUMP-3"]},
    };

    std::unordered_map<std::string, sf::IntRect> climb = {
        {"CLIMB-1", allSpritesLuigi["CLIMB-1"]},
        {"CLIMB-2", allSpritesLuigi["CLIMB-2"]},
    };

    std::unordered_map<std::string, sf::IntRect> victory = {
        {"VICTORY-1", allSpritesLuigi["VICTORY-1"]},
        {"VICTORY-2", allSpritesLuigi["VICTORY-2"]},
        {"VICTORY-3", allSpritesLuigi["VICTORY-3"]},
    };

    std::unordered_map<std::string, sf::IntRect> becomeBig = {
        {"BECOME_BIG-", allSpritesLuigi["BECOME_BIG-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigIdle = {
        {"isBig_IDLE-", allSpritesLuigi["isBig_IDLE-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigWalk1 = {
        {"isBig_WALK-1", allSpritesLuigi["isBig_WALK-1"]},
        {"isBig_WALK-2", allSpritesLuigi["isBig_WALK-2"]},
        {"isBig_WALK-3", allSpritesLuigi["isBig_WALK-1"]},
        {"isBig_WALK-4", allSpritesLuigi["isBig_IDLE-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigStop = {
        {"isBig_STOP-", allSpritesLuigi["isBig_STOP-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigRun1 = {
        {"isBig_RUN-1", allSpritesLuigi["isBig_RUN-1"]},
        {"isBig_RUN-2", allSpritesLuigi["isBig_WALK-1"]},
        {"isBig_RUN-3", allSpritesLuigi["isBig_WALK-2"]},
        {"isBig_RUN-4", allSpritesLuigi["isBig_WALK-1"]},
        {"isBig_RUN-5", allSpritesLuigi["isBig_IDLE-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigJump = {
        {"isBig_JUMP-1", allSpritesLuigi["isBig_JUMP-1"]},
        {"isBig_JUMP-2", allSpritesLuigi["isBig_JUMP-2"]},
        {"isBig_JUMP-3", allSpritesLuigi["isBig_JUMP-3"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigClimb = {
        {"isBig_CLIMB-1", allSpritesLuigi["isBig_CLIMB-1"]},
        {"isBig_CLIMB-2", allSpritesLuigi["isBig_CLIMB-2"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigCrouch = {
        {"isBig_CROUCH-", allSpritesLuigi["isBig_CROUCH-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigVictory = {
        {"isBig_VICTORY-1", allSpritesLuigi["isBig_VICTORY-1"]},
        {"isBig_VICTORY-2", allSpritesLuigi["isBig_VICTORY-2"]},
        {"isBig_VICTORY-3", allSpritesLuigi["isBig_VICTORY-3"]},
        {"isBig_VICTORY-4", allSpritesLuigi["isBig_VICTORY-4"]},
    };

    // Left

    std::unordered_map<std::string, sf::IntRect> idleR = {
        {"IDLER-", allSpritesLuigi["IDLER-"]},
    };

    std::unordered_map<std::string, sf::IntRect> walk1R = {
        {"WALKR-1", allSpritesLuigi["WALKR-1"]},
        {"WALKR-2", allSpritesLuigi["WALKR-2"]},
        {"WALKR-3", allSpritesLuigi["WALKR-1"]},
        {"WALKR-4", allSpritesLuigi["IDLER-"]},
    };

    std::unordered_map<std::string, sf::IntRect> stopR = {
        {"STOPR-", allSpritesLuigi["STOPR-"]},
    };

    std::unordered_map<std::string, sf::IntRect> run1R = {
        {"RUNR-1", allSpritesLuigi["RUNR-1"] },
        {"RUNR-2", allSpritesLuigi["WALKR-1"] },
        {"RUNR-3", allSpritesLuigi["WALKR-2"] },
        {"RUNR-4", allSpritesLuigi["WALKR-1"] },
        {"RUNR-5", allSpritesLuigi["IDLER-"] },
    };

    std::unordered_map<std::string, sf::IntRect> jumpR = {
        {"JUMPR-1", allSpritesLuigi["JUMPR-1"]},
        {"JUMPR-2", allSpritesLuigi["JUMPR-2"]},
        {"JUMPR-3", allSpritesLuigi["JUMPR-3"]},
    };

    std::unordered_map<std::string, sf::IntRect> climbR = {
        {"CLIMBR-1", allSpritesLuigi["CLIMBR-1"]},
        {"CLIMBR-2", allSpritesLuigi["CLIMBR-2"]},
    };

    std::unordered_map<std::string, sf::IntRect> victoryR = {
        {"VICTORYR-1", allSpritesLuigi["VICTORYR-1"]},
        {"VICTORYR-2", allSpritesLuigi["VICTORYR-2"]},
        {"VICTORYR-3", allSpritesLuigi["VICTORYR-3"]},
    };

    std::unordered_map<std::string, sf::IntRect> becomeBigR = {
        {"BECOME_BIGR-", allSpritesLuigi["BECOME_BIGR-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigIdleR = {
        {"isBig_IDLER-", allSpritesLuigi["isBig_IDLER-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigWalk1R = {
        {"isBig_WALKR-1", allSpritesLuigi["isBig_WALKR-1"]},
        {"isBig_WALKR-2", allSpritesLuigi["isBig_WALKR-2"]},
        {"isBig_WALKR-3", allSpritesLuigi["isBig_WALKR-1"]},
        {"isBig_WALKR-4", allSpritesLuigi["isBig_IDLER-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigStopR = {
        {"isBig_STOPR-", allSpritesLuigi["isBig_STOPR-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigRun1R = {
        {"isBig_RUNR-1", allSpritesLuigi["isBig_RUNR-1"]},
        {"isBig_RUNR-2", allSpritesLuigi["isBig_WALKR-1"]},
        {"isBig_RUNR-3", allSpritesLuigi["isBig_WALKR-2"]},
        {"isBig_RUNR-4", allSpritesLuigi["isBig_WALKR-1"]},
        {"isBig_RUNR-5", allSpritesLuigi["isBig_IDLER-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigJumpR = {
        {"isBig_JUMPR-1", allSpritesLuigi["isBig_JUMPR-1"]},
        {"isBig_JUMPR-2", allSpritesLuigi["isBig_JUMPR-2"]},
        {"isBig_JUMPR-3", allSpritesLuigi["isBig_JUMPR-3"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigClimbR = {
        {"isBig_CLIMBR-1", allSpritesLuigi["isBig_CLIMBR-1"]},
        {"isBig_CLIMBR-2", allSpritesLuigi["isBig_CLIMBR-2"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigCrouchR = {
        {"isBig_CROUCHR-", allSpritesLuigi["isBig_CROUCHR-"]},
    };

    std::unordered_map<std::string, sf::IntRect> isBigVictoryR = {
        {"isBig_VICTORYR-1", allSpritesLuigi["isBig_VICTORYR-1"]},
        {"isBig_VICTORYR-2", allSpritesLuigi["isBig_VICTORYR-2"]},
        {"isBig_VICTORYR-3", allSpritesLuigi["isBig_VICTORYR-3"]},
        {"isBig_VICTORYR-4", allSpritesLuigi["isBig_VICTORYR-4"]},
    };

    // Add right

    spritesSheet.insert(idle.begin(), idle.end());
    spritesSheet.insert(walk1.begin(), walk1.end());
    spritesSheet.insert(stop.begin(), stop.end());
    spritesSheet.insert(run1.begin(), run1.end());
    spritesSheet.insert(jump.begin(), jump.end());
    spritesSheet.insert(climb.begin(), climb.end());
    spritesSheet.insert(victory.begin(), victory.end());
    spritesSheet.insert(becomeBig.begin(), becomeBig.end());

    spritesSheet.insert(isBigIdle.begin(), isBigIdle.end());
    spritesSheet.insert(isBigWalk1.begin(), isBigWalk1.end());
    spritesSheet.insert(isBigStop.begin(), isBigStop.end());
    spritesSheet.insert(isBigRun1.begin(), isBigRun1.end());
    spritesSheet.insert(isBigJump.begin(), isBigJump.end());
    spritesSheet.insert(isBigClimb.begin(), isBigClimb.end());
    spritesSheet.insert(isBigCrouch.begin(), isBigCrouch.end());
    spritesSheet.insert(isBigVictory.begin(), isBigVictory.end());

    // Add left

    spritesSheet.insert(idleR.begin(), idleR.end());
    spritesSheet.insert(walk1R.begin(), walk1R.end());
    spritesSheet.insert(stopR.begin(), stopR.end());
    spritesSheet.insert(run1R.begin(), run1R.end());
    spritesSheet.insert(jumpR.begin(), jumpR.end());
    spritesSheet.insert(climbR.begin(), climbR.end());
    spritesSheet.insert(victoryR.begin(), victoryR.end());
    spritesSheet.insert(becomeBigR.begin(), becomeBigR.end());

    spritesSheet.insert(isBigIdleR.begin(), isBigIdleR.end());
    spritesSheet.insert(isBigWalk1R.begin(), isBigWalk1R.end());
    spritesSheet.insert(isBigStopR.begin(), isBigStopR.end());
    spritesSheet.insert(isBigRun1R.begin(), isBigRun1R.end());
    spritesSheet.insert(isBigJumpR.begin(), isBigJumpR.end());
    spritesSheet.insert(isBigClimbR.begin(), isBigClimbR.end());
    spritesSheet.insert(isBigCrouchR.begin(), isBigCrouchR.end());
    spritesSheet.insert(isBigVictoryR.begin(), isBigVictoryR.end());
}