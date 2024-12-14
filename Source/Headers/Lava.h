#pragma once
#include "PowerUpObject.h"
class Lava :
    public PowerUpObject
{
private:
	std::unordered_map<std::string, sf::IntRect> spritesSheet;
 public:
	Lava(sf::Vector2f position, sf::Vector2f size, std::string name);
	virtual ~Lava();

	void initSpritesSheet();
	void update(const float& dt) override;
	void render(sf::RenderTarget* target) override;
	void reactToCollison() override;
};

