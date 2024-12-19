#pragma once
#include "Block.h"

// This block will disappear and reappear after a certain amount of time

class CloudBlock :
    public Block
{
private:
    float curTime;
    const float appearTime = 4.f;
    const float disappearTime = 4.f;
public:
    CloudBlock(sf::Vector2f position, sf::Vector2f size, std::string name, float initTime);
	~CloudBlock();

    void initSpritesSheet();

	void update(const float& dt);
    void reactToCollison(int collidedSide);

    void render(sf::RenderTarget* target);
};

