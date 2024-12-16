#include "Headers/W3_LV1.h"

W3_LV1::W3_LV1(PlayerManager* player, sf::RenderWindow* window):
	LevelManager(player, window) 
{
	mapManager->convert_sketch(3, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();
}

W3_LV1::~W3_LV1() {

}

