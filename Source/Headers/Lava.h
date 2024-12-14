#pragma once
#include "Block.h"
class Lava :
    public Block
{
private:
	std::unordered_map<std::string, sf::IntRect> spritesSheet;
 public:
	Lava(sf::Vector2f position, sf::Vector2f size, std::string name);
	virtual ~Lava();

	void initSpritesSheet();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void reactToCollison(int collidedSide) override;
};

