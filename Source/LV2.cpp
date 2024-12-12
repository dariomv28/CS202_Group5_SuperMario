#include "Headers/LV2.h"

LV2::LV2(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2, Enemies, Blocks, PowerUps, player);
}


LV2::~LV2() {

}




