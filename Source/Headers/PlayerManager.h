#pragma once
#include "LivingEntity.h"
//#include "LevelManager.h"

class PlayerManager : 
    public LivingEntity {
public:
    PlayerManager(sf::Vector2f position, sf::Vector2f size, 
		int health, int speed, PhysicsEngine* physicEngine);
    PlayerManager() {};
    virtual ~PlayerManager();

    // Initialization function
    virtual void init();
    virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);
    std::string getImagePath() const;

	//void Move(const float& dt, const float dir_x, const float dir_y);

protected:
    std::string m_imagePath;
    
};

