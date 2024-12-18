#include "Headers/W2_LV1.h"

W2_LV1::W2_LV1(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2,1, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();
}


W2_LV1::~W2_LV1() {

}




