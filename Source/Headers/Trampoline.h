#pragma once
#include "Block.h"

class Trampoline :
    public Block
{
public:
	Trampoline();
	Trampoline(sf::Vector2f position, sf::Vector2f size, std::string name);
	~Trampoline();

	void initVariables();
	void initSpritesSheet();
	void update(const float& dt);
	void reactToCollison(int collidedSide);
	void render(sf::RenderTarget* target);

	void startBounceAnimation();
	void updateAnimation(const float& dt);

private:
	bool isCompressed = false;
	float animationTimer = 0.0f;
	int currentFrame = 1;
	bool shouldBounce = false;
};

