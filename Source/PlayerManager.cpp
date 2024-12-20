#include "Headers/PlayerManager.h"
#include "Headers/GameEventMediator.h"

PlayerManager::PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed)
    : LivingEntity(position, size, health, speed) {
    init();
    is_big = false;
    is_fire = false;

	allSpritesMario = {
		{ "IDLE", sf::IntRect(1, 17, 16, 16) },

		{ "WALK-1", sf::IntRect(17, 17, 16, 16) },
		{ "WALK-2", sf::IntRect(35, 17, 16, 16) },

		{ "STOP", sf::IntRect(52, 17, 16, 16)  },

		{ "RUN-1",  sf::IntRect(69, 17, 16, 16)  },

		{ "JUMP-1",  sf::IntRect(86, 17, 16, 16)  },
		{ "JUMP-2",  sf::IntRect(103, 17, 16, 16)  },
		{ "JUMP-3",  sf::IntRect(120, 17, 16, 16)  },

		{ "CLIMB-1",  sf::IntRect(138, 17, 16, 16)  },
		{ "CLIMB-2",  sf::IntRect(154, 17, 16, 16) },

		{ "VICTORY-1",  sf::IntRect(171, 17, 16, 16)  },
		{ "VICTORY-2",  sf::IntRect(188, 17, 16, 16)  },
		{ "VICTORY-3",  sf::IntRect(205, 17, 16, 16)  },

		{ "BECOME_BIG",  sf::IntRect(224, 3, 16, 30)  },

		{ "isBig_IDLE", sf::IntRect(241, 3, 14, 30)  },

		{ "isBig_WALK-1",  sf::IntRect(256, 3, 16, 30)  },
		{ "isBig_WALK-2",  sf::IntRect(273, 3, 16, 30)  },

		{ "isBig_STOP" ,  sf::IntRect(290, 2, 16, 30)  },

		{ "isBig_RUN-1",  sf::IntRect(307, 2, 16, 30)  },

		{ "isBig_JUMP-1",  sf::IntRect(328, 3, 20, 30)  },
		{ "isBig_JUMP-2",  sf::IntRect(354, 3, 20, 30)  },
		{ "isBig_JUMP-3",  sf::IntRect(378, 3, 20, 30)  },

		{ "isBig_CLIMB-1",  sf::IntRect(401, 3, 16, 30)  },
		{ "isBig_CLIMB-2",  sf::IntRect(418, 3, 16, 30)  },

		{ "isBig_CROUCH",  sf::IntRect(433, 3, 16, 32)  },

		{ "isBig_VICTORY-1",  sf::IntRect(450, 3, 16, 30)  },
		{ "isBig_VICTORY-2",  sf::IntRect(467, 3, 16, 30)  },
		{ "isBig_VICTORY-3",  sf::IntRect(484, 3, 16, 30)  },
		{ "isBig_VICTORY-4",  sf::IntRect(501, 3, 16, 30)  },
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
	buffs.push_back(buff);
}

void PlayerManager::removeBuff(PlayerBuff* buff) {
	buffs.erase(std::remove(buffs.begin(), buffs.end(), buff), buffs.end());
}


std::string PlayerManager::getImagePath() const {
    return m_imagePath;
}

void PlayerManager::setBig(bool big) {
	is_big = big;
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