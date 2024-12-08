#include "Headers/PlayerManager.h"
#include "Headers/GameEventMediator.h"

PlayerManager::PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed)
    : LivingEntity(position, size, health, speed) {
    init();
    is_big = false;
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



std::string PlayerManager::getImagePath() const {
    return m_imagePath;
}

void PlayerManager::setBig(bool big) {
	is_big = big;
}

bool PlayerManager::getBig() const {
	return is_big;
}
