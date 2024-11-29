#pragma once
#include "Block.h"

//The name is coin_block_x where x is the id of the coin block
class CoinBlock :
    public Block
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
	void reactToCollison(int collidedSide) override;
	void render(sf::RenderTarget* target) override;
};

