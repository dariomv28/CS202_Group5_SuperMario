#pragma once
#include "Block.h"

class Trampoline :
    public Block
{
public:
	Trampoline();
	Trampoline(sf::Vector2f position, sf::Vector2f size, std::string name);
	~Trampoline();

	void initSpritesSheet();
	void update(const float& dt);
	void reactToCollison(int collidedSide);
	void render(sf::RenderTarget* target);

	void updateAnimation(const float& dt);
	void startBounceAnimation();
	void initVariables();
private:
	bool isCompressed = false;
	bool shouldBounce = false;
	int currentFrame;
	float animationTimer;	
};

