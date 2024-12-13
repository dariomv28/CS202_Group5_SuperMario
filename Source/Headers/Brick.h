#pragma once
#include "Block.h"
class Brick :
    public Block
{
private:
    bool breakable;
public:
    Brick();
	Brick(sf::Vector2f position, sf::Vector2f size, std::string name, bool breakable = false);
	virtual ~Brick();

	//Setters and Getters
	void update(const float& dt) override;
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

