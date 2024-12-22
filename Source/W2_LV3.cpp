#include "Headers/W2_LV3.h"

W2_LV3::W2_LV3(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2, 3, Enemies, Blocks, PowerUps, player);

	initGameEventMediator();

	Blocks.push_back(new MovingBlock(sf::Vector2f(10400.f, 300.f), sf::Vector2f(64.f, 64.f), "snow_ground_mid", 100.f, 300.f));
}

W2_LV3::~W2_LV3() {

}