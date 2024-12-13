#pragma once
#include "Enemy.h"

class Goomba : public Enemy {
private:
	// Movement and positioning
	float walkSpeed;
	float x_min = 32.0f;
	float x_max = 13416.0f;

	bool isAlive;
	float disappearDelay = 0.0f;
	
	// Animation sprite sheet
	std::unordered_map<std::string, sf::IntRect> spritesSheet;

	// Current action string
	std::string currentAction;
	bool isAnimationInProgress;

	void initAnimations();
public:
	Goomba();
	Goomba(sf::Vector2f position, sf::Vector2f size, float x_min = 32.0f, float x_max = 13416.0f);

	void updateAnimation(const float& dt) override;

	// State getters and setters
	bool getIsAlive() const;
	void setIsAlive(bool alive);

	//update function
	void update(const float& dt) override;

	// Collision response
	void move(const float& dt) override;
	void reactToPlayerCollision(int collidedSide) override;
};
