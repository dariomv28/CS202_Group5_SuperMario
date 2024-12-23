#include "Headers/PlayerManager.h"
#include "Headers/GameEventMediator.h"
#include "Headers/PlayerBuff.h"
#include "Headers/FireBuff.h"

PlayerManager::PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed)
    : LivingEntity(position, size, health, speed), currentAction("IDLE-"), isAnimationInProgress(false), transformationTimer(0.0f) {

    init();
    is_big = false;
    is_fire = false;

	allSpritesMario = {
		{ "IDLE-", sf::IntRect(1, 17, 16, 16) },

		{ "WALK-1", sf::IntRect(17, 17, 16, 16) },
		{ "WALK-2", sf::IntRect(35, 17, 16, 16) },

		{ "STOP-", sf::IntRect(52, 17, 16, 16)  },

		{ "RUN-1",  sf::IntRect(69, 17, 16, 16)  },

		{ "JUMP-1",  sf::IntRect(86, 17, 16, 16)  },
		{ "JUMP-2",  sf::IntRect(103, 17, 16, 16)  },
		{ "JUMP-3",  sf::IntRect(120, 17, 16, 16)  },

		{ "CLIMB-1",  sf::IntRect(138, 17, 16, 16)  },
		{ "CLIMB-2",  sf::IntRect(154, 17, 16, 16) },

		{ "VICTORY-1",  sf::IntRect(171, 17, 16, 16)  },
		{ "VICTORY-2",  sf::IntRect(188, 17, 16, 16)  },
		{ "VICTORY-3",  sf::IntRect(205, 17, 16, 16)  },

		{ "BECOME_BIG-",  sf::IntRect(224, 3, 16, 30)  },

		{ "isBig_IDLE-", sf::IntRect(241, 3, 14, 30)  },

		{ "isBig_WALK-1",  sf::IntRect(256, 3, 16, 30)  },
		{ "isBig_WALK-2",  sf::IntRect(273, 3, 16, 30)  },

		{ "isBig_STOP-" ,  sf::IntRect(290, 2, 16, 32)  },

		{ "isBig_RUN-1",  sf::IntRect(307, 2, 16, 32)  },

		{ "isBig_JUMP-1",  sf::IntRect(328, 3, 20, 30)  },
		{ "isBig_JUMP-2",  sf::IntRect(354, 3, 20, 30)  },
		{ "isBig_JUMP-3",  sf::IntRect(378, 3, 20, 30)  },

		{ "isBig_CLIMB-1",  sf::IntRect(401, 3, 16, 30)  },
		{ "isBig_CLIMB-2",  sf::IntRect(418, 3, 16, 30)  },

		{ "isBig_CROUCH-",  sf::IntRect(433, 3, 16, 30)  },

		{ "isBig_VICTORY-1",  sf::IntRect(450, 3, 16, 30)  },
		{ "isBig_VICTORY-2",  sf::IntRect(467, 3, 16, 30)  },
		{ "isBig_VICTORY-3",  sf::IntRect(484, 3, 16, 30)  },
		{ "isBig_VICTORY-4",  sf::IntRect(501, 3, 16, 30)  },

		{ "IDLER-", sf::IntRect(1056, 17, 16, 16) },

		{ "WALKR-1", sf::IntRect(1039, 17, 16, 16) },
		{ "WALKR-2", sf::IntRect(1022, 17, 16, 16) },

		{ "STOPR-", sf::IntRect(1006, 17, 16, 16)  },

		{ "RUNR-1",  sf::IntRect(988, 17, 16, 16)  },

		{ "JUMPR-1",  sf::IntRect(971, 17, 16, 16)  },
		{ "JUMPR-2",  sf::IntRect(955, 17, 16, 16)  },
		{ "JUMPR-3",  sf::IntRect(938, 17, 16, 16)  },

		{ "CLIMBR-1",  sf::IntRect(920, 17, 16, 16)  },
		{ "CLIMBR-2",  sf::IntRect(903, 17, 16, 16) },

		{ "VICTORYR-1",  sf::IntRect(886, 17, 16, 16)  },
		{ "VICTORYR-2",  sf::IntRect(869, 17, 16, 16)  },
		{ "VICTORYR-3",  sf::IntRect(852, 17, 16, 16)  },

		{ "BECOME_BIGR-",  sf::IntRect(834, 3, 16, 30)  },

		{ "isBig_IDLER-", sf::IntRect(818, 3, 14, 30)  },

		{ "isBig_WALKR-1",  sf::IntRect(801, 3, 16, 30)  },
		{ "isBig_WALKR-2",  sf::IntRect(784, 3, 16, 30)  },

		{ "isBig_STOPR-" ,  sf::IntRect(767, 2, 16, 32)  },

		{ "isBig_RUNR-1",  sf::IntRect(750, 2, 16, 32)  },

		{ "isBig_JUMPR-1",  sf::IntRect(725, 3, 20, 30)  },
		{ "isBig_JUMPR-2",  sf::IntRect(699, 3, 20, 30)  },
		{ "isBig_JUMPR-3",  sf::IntRect(675, 3, 20, 30)  },

		{ "isBig_CLIMBR-1",  sf::IntRect(657, 3, 16, 30)  },
		{ "isBig_CLIMBR-2",  sf::IntRect(640, 3, 16, 30)  },

		{ "isBig_CROUCHR-",  sf::IntRect(624, 3, 16, 30)  },

		{ "isBig_VICTORYR-1",  sf::IntRect(607, 3, 16, 30)  },
		{ "isBig_VICTORYR-2",  sf::IntRect(590, 3, 16, 30)  },
		{ "isBig_VICTORYR-3",  sf::IntRect(573, 3, 16, 30)  },
		{ "isBig_VICTORYR-4",  sf::IntRect(556, 3, 16, 30)  },
	};

	allSpritesLuigi = {
		{ "IDLE-", sf::IntRect(1, 50, 16, 16) },

		{ "WALK-1", sf::IntRect(17, 50, 16, 16) },
		{ "WALK-2", sf::IntRect(35, 50, 16, 16) },

		{ "STOP-", sf::IntRect(52, 50, 16, 16) },

		{ "RUN-1",  sf::IntRect(69, 50, 16, 16) },

		{ "JUMP-1",  sf::IntRect(86, 50, 16, 16) },
		{ "JUMP-2",  sf::IntRect(103, 50, 16, 16) },
		{ "JUMP-3",  sf::IntRect(120, 50, 16, 16) },

		{ "CLIMB-1",  sf::IntRect(138, 50, 16, 16) },
		{ "CLIMB-2",  sf::IntRect(154, 50, 16, 16) },

		{ "VICTORY-1",  sf::IntRect(171, 50, 16, 16) },
		{ "VICTORY-2",  sf::IntRect(188, 50, 16, 16) },
		{ "VICTORY-3",  sf::IntRect(205, 50, 16, 16) },

		{ "BECOME_BIG-",  sf::IntRect(224, 35, 16, 30) },

		{ "isBig_IDLE-", sf::IntRect(241, 35, 14, 30) },

		{ "isBig_WALK-1",  sf::IntRect(256, 35, 16, 30) },
		{ "isBig_WALK-2",  sf::IntRect(273, 35, 16, 30) },

		{ "isBig_STOP-" ,  sf::IntRect(290, 34, 16, 32) },

		{ "isBig_RUN-1",  sf::IntRect(307, 35, 16, 32) },

		{ "isBig_JUMP-1",  sf::IntRect(328, 35, 20, 30) },
		{ "isBig_JUMP-2",  sf::IntRect(354, 35, 20, 30) },
		{ "isBig_JUMP-3",  sf::IntRect(378, 35, 20, 30) },

		{ "isBig_CLIMB-1",  sf::IntRect(401, 35, 16, 30) },
		{ "isBig_CLIMB-2",  sf::IntRect(418, 35, 16, 30) },

		{ "isBig_CROUCH-",  sf::IntRect(433, 35, 16, 30) },

		{ "isBig_VICTORY-1",  sf::IntRect(450, 35, 16, 30) },
		{ "isBig_VICTORY-2",  sf::IntRect(467, 35, 16, 30) },
		{ "isBig_VICTORY-3",  sf::IntRect(484, 35, 16, 30) },
		{ "isBig_VICTORY-4",  sf::IntRect(501, 35, 16, 30) },

		{ "IDLER-", sf::IntRect(1056, 50, 16, 16) },

		{ "WALKR-1", sf::IntRect(1039, 50, 16, 16) },
		{ "WALKR-2", sf::IntRect(1022, 50, 16, 16) },

		{ "STOPR-", sf::IntRect(1006, 50, 16, 16) },

		{ "RUNR-1",  sf::IntRect(988, 50, 16, 16) },

		{ "JUMPR-1",  sf::IntRect(971, 50, 16, 16) },
		{ "JUMPR-2",  sf::IntRect(955, 50, 16, 16) },
		{ "JUMPR-3",  sf::IntRect(938, 50, 16, 16) },

		{ "CLIMBR-1",  sf::IntRect(920, 50, 16, 16) },
		{ "CLIMBR-2",  sf::IntRect(903, 50, 16, 16) },

		{ "VICTORYR-1",  sf::IntRect(886, 50, 16, 16) },
		{ "VICTORYR-2",  sf::IntRect(869, 50, 16, 16) },
		{ "VICTORYR-3",  sf::IntRect(852, 50, 16, 16) },

		{ "BECOME_BIGR-",  sf::IntRect(834, 35, 16, 30) },

		{ "isBig_IDLER-", sf::IntRect(818, 35, 14, 30) },

		{ "isBig_WALKR-1",  sf::IntRect(801, 35, 16, 30) },
		{ "isBig_WALKR-2",  sf::IntRect(784, 35, 16, 30) },

		{ "isBig_STOPR-" ,  sf::IntRect(767, 34, 16, 32) },

		{ "isBig_RUNR-1",  sf::IntRect(750, 35, 16, 32) },

		{ "isBig_JUMPR-1",  sf::IntRect(725, 35, 20, 30) },
		{ "isBig_JUMPR-2",  sf::IntRect(699, 35, 20, 30) },
		{ "isBig_JUMPR-3",  sf::IntRect(675, 35, 20, 30) },

		{ "isBig_CLIMBR-1",  sf::IntRect(657, 35, 16, 30) },
		{ "isBig_CLIMBR-2",  sf::IntRect(640, 35, 16, 30) },

		{ "isBig_CROUCHR-",  sf::IntRect(624, 35, 16, 30) },

		{ "isBig_VICTORYR-1",  sf::IntRect(607, 35, 16, 30) },
		{ "isBig_VICTORYR-2",  sf::IntRect(590, 35, 16, 30) },
		{ "isBig_VICTORYR-3",  sf::IntRect(573, 35, 16, 30) },
		{ "isBig_VICTORYR-4",  sf::IntRect(556, 35, 16, 30) },
	};

};

PlayerManager::~PlayerManager() {
}

void PlayerManager::init() {
    m_imagePath = "Source/Resources/texture/Mario_Luigi_logo.png";
}

void PlayerManager::update(const float& dt) {
	updateAnimation(dt);
	updateHitboxSize();
	//std::cout << "Position x: " << position.x << " Position y: " << position.y << std::endl;
	updateVelocity(dt);
	eventMediator->applyExternalForce(this, dt);
	move(dt);
	for (auto& buff : buffs) {
		buff->applyBuff(this->eventMediator);
	}
}

void PlayerManager::render(sf::RenderTarget* target) {
	if (target) {
		target->draw(entitySprite);
		//std::cout << this->getOnGround() << std::endl;
	}
	else {
		std::cerr << "Render target is null!" << std::endl;
	}
}

void PlayerManager::updateHitboxSize() {
	if (is_big) {
		if (currentAction == "JUMP-") {
			hitbox.setSize(sf::Vector2f(80.f, 128.f));
		}
		else if (currentAction == "CROUCH-") {
			hitbox.setSize(sf::Vector2f(64.f, 120.f));
		}
		else {
			hitbox.setSize(sf::Vector2f(64.f, 122.f));
		}
	}
	else {
		hitbox.setSize(sf::Vector2f(64.f, 64.f));
	}
	hitbox.setPosition(position);
}

void PlayerManager::handleInput(const float& dt) {
	// Reset movement flags
	movementComponent->isMoveLeft = false;
	movementComponent->isMoveRight = false;
	movementComponent->isJump = false;

	bool isWalking = false;
	bool isRunning = false;
	bool isCrouching = false;

	// Simultaneous movement and jump handling
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		movementComponent->isMoveLeft = true;
		entitySprite.setScale(4.0f, 4.0f);
		isWalking = true;
		isMovingLeft = true;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		movementComponent->isMoveRight = true;
		entitySprite.setScale(4.0f, 4.0f);
		isWalking = true;
		isMovingLeft = false;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		if (is_big) {
			currentAction = "CROUCH";
			isAnimationInProgress = true;
			isCrouching = true;
		}
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)) {
		isRunning = true;
	}

	if (isRunning) {
		movementComponent->maxVelocity = 4.0f * 100 + 150.0f;
	}
	else {
		movementComponent->maxVelocity = 4.0f * 100;
	}

	// Improved jump handling
	static bool spaceWasPressed = false;
	bool spaceIsPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::W) ||
		sf::Keyboard::isKeyPressed(sf::Keyboard::Up);

	// Immediate jump request when space is first pressed
	if (spaceIsPressed && !spaceWasPressed) {
		if (movementComponent->getJumpsRemaining() > 0) {
			eventMediator->playJumpSound();
		}
		movementComponent->isJump = true;
		currentAction = "JUMP-";
		isAnimationInProgress = true;

		// Reset jump animation if needed
		if (!movementComponent->onGround && movementComponent->getJumpsRemaining() > 0) {
			animationComponent->currentFrameIndex = 0;
			animationComponent->elapsedTime = 0;
		}
	}
	spaceWasPressed = spaceIsPressed;

	// Animation and action state management
	if (currentAction != "JUMP-") {
		if (isWalking && isRunning) {
			currentAction = "RUN-";
		}
		else if (isWalking) {
			currentAction = "WALK-";
		}
		else if (isCrouching) {
			currentAction = "CROUCH-";
		}
		else {
			currentAction = "IDLE-";
		}
	}
}

void PlayerManager::updateAnimation(const float& dt) {
	if (isTransforming) {
		transformationTimer += dt;

		if (transformationTimer >= TRANSFORMATION_DURATION) {
			isTransforming = false;
			transformationTimer = 0.f;
			currentAction = isMovingLeft ? "IDLER-" : "IDLE-";
		}
		else {
			if (isMovingLeft) {
				animationComponent->setAnimation("BECOME_BIGR-", spritesSheet, 0.2f, false);
			}
			else {
				animationComponent->setAnimation("BECOME_BIG-", spritesSheet, 0.2f, false);
			}
		}

		animationComponent->update(dt);
		return;
	}

	std::string prefix = is_big ? "isBig_" : "";
	bool animationSet = false;

	if (currentAction == "JUMP-") {
		// Use a faster animation speed to make sure we see the jump frames
		if (isMovingLeft) {
			animationComponent->setAnimation(prefix + "JUMPR-", spritesSheet, 0.2f, is_big);
			animationSet = true;

			// If the jump animation has completed and we're on the ground
			if (animationComponent->currentFrameIndex == animationComponent->currentAnimationFrames.size() - 1
				&& movementComponent->onGround) {
				currentAction = "IDLER-";
			}
		}
		else {
			animationComponent->setAnimation(prefix + "JUMP-", spritesSheet, 0.2f, is_big);
			animationSet = true;

			// If the jump animation has completed and we're on the ground
			if (animationComponent->currentFrameIndex == animationComponent->currentAnimationFrames.size() - 1
				&& movementComponent->onGround) {
				currentAction = "IDLE-";
			}
		}
	}
	else if (currentAction == "RUN-") {
		if (isMovingLeft) {
			animationComponent->setAnimation(prefix + "RUNR-", spritesSheet, 0.15f, is_big);
			animationSet = true;
		}
		else {
			animationComponent->setAnimation(prefix + "RUN-", spritesSheet, 0.15f, is_big);
			animationSet = true;
		}
	}
	else if (currentAction == "WALK-") {
		if (isMovingLeft) {
			animationComponent->setAnimation(prefix + "WALKR-", spritesSheet, 0.2f, is_big);
			animationSet = true;
		}
		else {
			animationComponent->setAnimation(prefix + "WALK-", spritesSheet, 0.2f, is_big);
			animationSet = true;
		}
	}
	else if (currentAction == "CROUCH-") {
		if (isMovingLeft) {
			animationComponent->setAnimation(prefix + "CROUCHR-", spritesSheet, 0.2f, is_big);
			animationSet = true;
		}
		else {
			animationComponent->setAnimation(prefix + "CROUCH-", spritesSheet, 0.2f, is_big);
			animationSet = true;
		}
	}

	if (!animationSet) {
		if (isMovingLeft) {
			animationComponent->setAnimation(prefix + "IDLER-", spritesSheet, 0.5f, is_big);
		}
		else {
			animationComponent->setAnimation(prefix + "IDLE-", spritesSheet, 0.5f, is_big);
		}
	}

	animationComponent->update(0.016f);
}

void PlayerManager::addBuff(PlayerBuff* buff) {
    // Check if the buff is already applied
    for (auto b : buffs) {
		if (b->getType() == buff->getType()) {
			return;
		}
	}
	buffs.push_back(buff);
}

void PlayerManager::removeBuff(std::string type) {
	for (int i = 0; i < buffs.size(); i++) {
		if (buffs[i]->getType() == type) {
			buffs.erase(buffs.begin() + i);
			return;
		}
	}
}


std::string PlayerManager::getImagePath() const {
    return m_imagePath;
}

void PlayerManager::setBig(bool big) {
	if (big == is_big) {
		return;
	}

	if (big == true) {
		// Start transformation animation
		isTransforming = true;
		currentAction = "BECOME_BIG-";
	}

	if (big == true) {
		addBuff(new FireBuff());
	}
	else {
		removeBuff("fire");
	}

	// The actual size change will happen after animation completes
	is_big = big;
	updateHitboxSize();
}

bool PlayerManager::getBig() const {
	return is_big;
}

int PlayerManager::getHealth() const {
    return this->health;
}

void PlayerManager::setHealth(int health) {
    if (health >= 0) {
        this->health = health;
    }
}

void PlayerManager::Save(std::ofstream& file)
{
	if (file.is_open())
	{
		file << m_name << std::endl;
		file << position.x << " " << position.y << std::endl;
		file << health << std::endl;
		file << speed << std::endl;
		file << is_big << std::endl;

	}
	else
	{
		std::cerr << "Unable to save game!" << std::endl;
	}

	std::cerr << "SaveGame.txt" << std::endl;
}

void PlayerManager::Load(std::ifstream& file)
{
	if (file.is_open())
	{
		std::string name;
		file >> name;
		file >> position.x >> position.y;
		file >> health;
		file >> speed;
		file >> is_big;
	}
	else
	{
		std::cerr << "Unable to load game!" << std::endl;
	}
}

void PlayerManager::getRemainInfo()
{
}