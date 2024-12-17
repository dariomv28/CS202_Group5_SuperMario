#include "Headers/W1_LV3.h"

W1_LV3::W1_LV3(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(1, 3, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();
}

W1_LV3::~W1_LV3() {

}