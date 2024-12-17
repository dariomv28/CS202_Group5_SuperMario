#include "Headers/W2_LV2.h"

W2_LV2::W2_LV2(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2, 2, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();
}

W2_LV2::~W2_LV2() {

}