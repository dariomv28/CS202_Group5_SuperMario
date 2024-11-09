#include "Headers/PlayerManager.h"

PlayerManager::PlayerManager() {
    
}

PlayerManager::~PlayerManager() {
    
}

void PlayerManager::init() {
    
    m_imagePath = "resources/texture/Mario_Luigi.png";
}

std::string PlayerManager::getImagePath() const {
    return m_imagePath;
}
