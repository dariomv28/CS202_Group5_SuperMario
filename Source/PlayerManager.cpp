#include "Headers/PlayerManager.h"
#include "Headers/GameEventMediator.h"
#include "Headers/PlayerBuff.h"
#include "Headers/FireBuff.h"

PlayerManager::PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed)
    : LivingEntity(position, size, health, speed) {
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
}

void PlayerManager::render(sf::RenderTarget* target) {
}

void PlayerManager::handleInput(const float& dt) {
}

void PlayerManager::updateAnimation(const float& dt) {
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
	//Change the size of the player
	if (big == is_big) return;
	if (big) {
		is_big = true;
		addBuff(new FireBuff());
		setSize(sf::Vector2f(CELL_SIZE, 2*CELL_SIZE));
		setPosition(getPosition().x, getPosition().y - CELL_SIZE);
	}
	else {
		is_big = false;
		removeBuff("fire");
		setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
		setPosition(getPosition().x, getPosition().y + CELL_SIZE);
	}
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