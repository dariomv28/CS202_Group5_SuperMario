#include "Headers/PlayerManager.h"
#include "Headers/PhysicsEngine.h"

PlayerManager::PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed, PhysicsEngine* physicEngine) :
	LivingEntity(position, size, health, speed, physicEngine) {
	init();
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


std::string PlayerManager::getImagePath() const {
    return m_imagePath;
}
