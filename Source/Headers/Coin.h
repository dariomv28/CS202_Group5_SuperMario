#pragma once
#include "PowerUpObject.h"

//Name = "coin"
class Coin :
    public PowerUpObject
{
private:
	float coinAnimationTimer = 0.0f;
	int coinAnimationCurrentFrame = 0;
public:
    Coin();
	Coin(sf::Vector2f position, sf::Vector2f size, std::string name);
	virtual ~Coin();
	void update(const float& dt) override;
	void reactToCollison() override;
	void render(sf::RenderTarget* target) override;

	void updateAnimation(const float& dt);
};

