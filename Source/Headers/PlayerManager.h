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

    std::unordered_map<std::string, sf::IntRect> allSpritesMario;
    std::unordered_map<std::string, sf::IntRect> allSpritesLuigi;

    // Transformation
    const float TRANSFORMATION_DURATION = 0.5f;
    float transformationTimer;
    bool isTransforming;

    // Animation
    std::string m_name;
    std::string currentAction;
    bool isAnimationInProgress;
    std::unordered_map<std::string, sf::IntRect> spritesSheet;

    // Flashing when losing health
    float flashDuration;
    float flashTimer;
    float flashInterval;
    bool isVisible;

public:
    PlayerManager(sf::Vector2f position, sf::Vector2f size, int health, int speed);
    virtual ~PlayerManager();

    //Setters and Getters
    std::string getImagePath() const;

    bool immortal;
    bool isFlashing;

    // Initialization function
    virtual void init();
    
    // Functions
    virtual void handleInput(const float& dt);
    virtual void updateAnimation(const float& dt);
    virtual void update(const float& dt);
	virtual void render(sf::RenderTarget* target);

    // Buffs
    virtual void addBuff(PlayerBuff* buff);
    virtual void removeBuff(std::string type);

    // Setters and Getters
    void setBig(bool big);
    bool getBig() const;
    int getHealth() const;
    void setHealth(int health);
    virtual void Save(std::ofstream& file);
	virtual void Load(std::ifstream& file);
    virtual void getRemainInfo();

	void updateHitboxSize();

    // Flashing 
    void startFlashing();
};

