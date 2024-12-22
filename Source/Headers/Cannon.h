#pragma once
#include "Block.h"
class Cannon :
    public Block
{
private:
	const float reloadDuration = 5.0f;
	float reloadTimer;
public:
	Cannon();
	Cannon(sf::Vector2f position, sf::Vector2f size, std::string name);
	~Cannon();

	void initSpritesSheet();
	void update(const float& dt);
	void reactToCollison(int collidedSide);
	void render(sf::RenderTarget* target);
};

