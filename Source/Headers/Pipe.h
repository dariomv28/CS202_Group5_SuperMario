#pragma once
#include "Block.h"
#include "SolidBlock.h"

class Pipe :
    public Block
{
private:
    std::vector<sf::Texture> texture_pipe;
	std::vector<sf::Sprite> sprite_pipe;
    int height;
public:
    Pipe();
	Pipe(sf::Vector2f position, sf::Vector2f size, std::string name, int height);
	virtual ~Pipe();

	//Setters and Getters
	void update(const float& dt) override;
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

