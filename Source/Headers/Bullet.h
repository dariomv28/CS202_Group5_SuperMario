#pragma once
#include "PowerUpObject.h"
class Bullet :
    public PowerUpObject
{
private:
	sf::Vector2f velocity;
	std::string sender;
	float animationTimer;
	int animationCurrentFrame;
public:
	Bullet(sf::Vector2f position, sf::Vector2f size, std::string name, std::string sender, sf::Vector2f velocity);
	virtual ~Bullet();

	void initSpritesSheet();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void reactToCollison();
	void reactToEnemyCollision(Enemy* enemy) override;
	void reactToBlockCollision(Block* block) override;
	void updateAnimation(const float& dt);
};

