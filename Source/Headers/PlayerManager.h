#pragma once
#include "LivingEntity.h"
#include "PlayerBuff.h"

class PlayerBuff;

class PlayerManager : 
    public LivingEntity {
protected:
    std::string m_imagePath;
    bool is_big;
    bool buffed_fire;
    bool is_fire;
    std::vector<PlayerBuff*> buffs;

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

    // Buffs
    virtual void addBuff(PlayerBuff* buff);
    virtual void removeBuff(PlayerBuff* buff);

    // Setters and Getters
    void setBig(bool big);
    bool getBig() const;
};

