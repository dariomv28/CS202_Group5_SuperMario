#include "Headers/PlayerManager.h"
#include "Headers/GameEventMediator.h"

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