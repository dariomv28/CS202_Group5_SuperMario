#include "Headers/W2_LV2.h"

W2_LV2::W2_LV2(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2, 2, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();

	Blocks.push_back(new MovingBlock(sf::Vector2f(2200.f, 300.f), sf::Vector2f(64.f, 64.f), "snow_ground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(2800.f, 300.f), sf::Vector2f(64.f, 64.f), "snow_ground_mid", 100.f, 300.f));
}

W2_LV2::~W2_LV2() {

}