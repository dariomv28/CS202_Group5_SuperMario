#pragma once
#include "PowerUpObject.h"
class Bullet :
    public PowerUpObject
{
private:
	sf::Vector2f velocity;
public:
	Bullet(sf::Vector2f position, sf::Vector2f size, std::string name, sf::Vector2f velocity);
	virtual ~Bullet();

	void initSpritesSheet();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void reactToCollision(int entity);
};

