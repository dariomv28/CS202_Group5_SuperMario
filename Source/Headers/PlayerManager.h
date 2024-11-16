#pragma once
#include "LivingEntity.h"

class PlayerManager : 
    public LivingEntity {
public:
    PlayerManager(sf::Vector2f position, sf::Vector2f size, 
		int health, int speed, PhysicsEngine* physicEngine);
    PlayerManager() {};
    virtual ~PlayerManager();

    // Initialization function
    virtual void init();
    std::string getImagePath() const;

protected:
    std::string m_imagePath;
};

