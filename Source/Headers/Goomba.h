#pragma once
#include "Enemy.h"

class Goomba : public Enemy {
private:
	std::unordered_map<std::string, sf::IntRect> spritesSheet;
	std::string currentAction;
	bool isAnimationInProgress;

	float walkSpeed;
	bool isAlive;

	float x_min = 32.0f;
	float x_max = 13416.0f;

	float disappearDelay = 0.0f;

	void initAnimations();
public:
	Goomba();
	Goomba(sf::Vector2f position, sf::Vector2f size, float x_min = 32.0f, float x_max = 13416.0f);

	void update(const float& dt) override;
	void updateAnimation(const float& dt) override;

	bool getIsAlive() const;
	void setIsAlive(bool alive);

	void move(const float& dt) override;
	void reactToPlayerCollision(int collidedSide) override;
};
