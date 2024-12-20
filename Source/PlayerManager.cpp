#include "Headers/PlayerManager.h"
#include "Headers/GameEventMediator.h"
#include "Headers/PlayerBuff.h"

PlayerManager::PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed)
    : LivingEntity(position, size, health, speed) {
    init();
    is_big = false;
    is_fire = false;
}

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

void PlayerManager::removeBuff(PlayerBuff* buff) {
	buffs.erase(std::remove(buffs.begin(), buffs.end(), buff), buffs.end());
}


std::string PlayerManager::getImagePath() const {
    return m_imagePath;
}

void PlayerManager::setBig(bool big) {
	//Change the size of the player
	if (big) {
		is_big = true;
		setSize(sf::Vector2f(CELL_SIZE, 2*CELL_SIZE));
		setPosition(getPosition().x, getPosition().y - CELL_SIZE);
	}
	else {
		is_big = false;
		setSize(sf::Vector2f(CELL_SIZE,CELL_SIZE));
		setPosition(getPosition().x, getPosition().y + CELL_SIZE);
	}
}

bool PlayerManager::getBig() const {
	return is_big;
}
