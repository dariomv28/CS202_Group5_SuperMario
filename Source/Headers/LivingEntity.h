#pragma once
#include "GameObject.h"
#include "AnimationComponent.h"
#include "MovementComponent.h"

class LivingEntity :
    public GameObject
{
protected:
    int health;
	int speed;
public:
	LivingEntity();
	LivingEntity(sf::Vector2f position, sf::Vector2f size, 
				int health, int speed);
	virtual ~LivingEntity();
		
	//Setters and Getters
	void setHealth(int health);
	int getHealth() const;
	void setSpeed(int speed);
	int getSpeed() const;
	//void setIsDefeated(bool isDefeated);
	//bool getIsDefeated() const;
	void setOnGround(bool onGround);
	bool getOnGround() const;
	void setHitCeiling(bool hitCeiling);
	bool getHitCeiling() const;
	void setVelocity(sf::Vector2f velocity);
	sf::Vector2f getVelocity() const;
	bool isMoveLeft() const;
	void setMoveLeft(bool moveLeft);
	bool isMoveRight() const;
	void setMoveRight(bool moveRight);
	bool isJump() const;
	void setJump(bool jump);

	bool isMovingLeft;

	//Functions
	void updateVelocity(const float& dt);
	virtual void move(const float& dt);
	virtual void updateAnimation(const float& dt) = 0;
	virtual void update(const float& dt) override;
	virtual void render(sf::RenderTarget* target) override;

	AnimationComponent* animationComponent;
	MovementComponent* movementComponent;
};

