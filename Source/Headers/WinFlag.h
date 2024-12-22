#pragma once
#include "Block.h"
class WinFlag :
    public Block
{
public:
	WinFlag();
	WinFlag(sf::Vector2f position, sf::Vector2f size, std::string name);
	~WinFlag();

	void initSpritesSheet();
	void update(const float& dt);
	void reactToCollison(int collidedSide);
	void render(sf::RenderTarget* target);
};

