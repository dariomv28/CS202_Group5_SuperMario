#pragma once
#include "SolidBlock.h"
class CoinBlock :
    public SolidBlock
{
private:
	int numCoins;

public:
	CoinBlock();
	CoinBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int numCoins = 3);
	virtual ~CoinBlock();
	//void initSpritesSheet();

	//Setters and Getters
	void update(const float& dt) override;
	void reactToObject(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

