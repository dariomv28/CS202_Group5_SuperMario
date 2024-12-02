#pragma once
#include "Enemy.h"

class Goomba : public Enemy {
private:
	std::unordered_map<std::string, sf::IntRect> spritesSheet;
	std::string currentAction;
	bool isAnimationInProgress;

	float walkSpeed;
	bool isAlive;

	void initAnimations();
public:
	Goomba();
	Goomba(sf::Vector2f position, sf::Vector2f size);

	void update(const float& dt) override;
	void updateAnimation(const float& dt) override;
	void moveWithView(const float& dt, const sf::View& view);

	bool getIsAlive() const;
	void setIsAlive(bool alive);
};
