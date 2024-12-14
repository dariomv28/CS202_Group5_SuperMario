#include "Headers/LV3.h"

LV3::LV3(PlayerManager* player, sf::RenderWindow* window):
	LevelManager(player, window) 
{
	mapManager->convert_sketch(3, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();
}

LV3::~LV3() {

}

