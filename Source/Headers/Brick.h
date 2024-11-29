#pragma once
#include "Block.h"
class Brick :
    public Block
{
private:
    int hiddenObject;
public:
    Brick();
	Brick(sf::Vector2f position, sf::Vector2f size, std::string name, int hiddenObject = 0);
	virtual ~Brick();

	//Setters and Getters
	void update(const float& dt) override;
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

