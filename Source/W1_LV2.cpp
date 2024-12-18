#include "Headers/W1_LV2.h"

W1_LV2::W1_LV2(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(1, 2, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();
}

W1_LV2::~W1_LV2() {

}