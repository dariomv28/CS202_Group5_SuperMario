#pragma once
#include "LivingEntity.h"
//#include "LevelManager.h"

class PlayerManager : 
    public LivingEntity {
public:

    PlayerManager(sf::Vector2f position, sf::Vector2f size, 
		int health, int speed);
    PlayerManager() {};
    virtual ~PlayerManager();

    //Setters and Getters
    std::string getImagePath() const;

    // Initialization function
    virtual void init();
    
    // Functions
    virtual void handleInput(const float& dt);
    virtual void updateAnimation(const float& dt);
    virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

    
protected:
    std::string m_imagePath;
  
};

