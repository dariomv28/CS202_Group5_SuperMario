#pragma once
#include "PowerUpObject.h"
class Rocket :
    public PowerUpObject
{
private:
    sf::Vector2f velocity;
	float existTime;
    const float maxTime = 7.5f;
public:
	Rocket(sf::Vector2f position, sf::Vector2f size, std::string name, sf::Vector2f velocity);
	virtual ~Rocket();

	void initSpritesSheet();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void reactToCollison();
	void reactToEnemyCollision(Enemy* enemy) override;
	void reactToBlockCollision(Block* block) override;
	void updateAnimation(const float& dt);
   
};

