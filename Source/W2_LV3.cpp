#include "Headers/W2_LV3.h"

W2_LV3::W2_LV3(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2, 3, Enemies, Blocks, PowerUps, player);

	initGameEventMediator();
}

W2_LV3::~W2_LV3() {

}