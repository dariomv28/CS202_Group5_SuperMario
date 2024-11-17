#include "Headers/PlayerManager.h"

PlayerManager::PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed, PhysicsEngine* physicEngine) :
	LivingEntity(position, size, health, speed, physicEngine) {
	init();
}

PlayerManager::~PlayerManager() {
    
}

void PlayerManager::init() {
    
    m_imagePath = "Source/Resources/texture/Mario_Luigi_logo.png";
}

std::string PlayerManager::getImagePath() const {
    return m_imagePath;
}
