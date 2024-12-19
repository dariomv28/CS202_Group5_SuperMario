#include "Headers/W1_LV1.h"
#include <iostream>


W1_LV1::W1_LV1(PlayerManager* player, sf::RenderWindow *window):
	LevelManager(player, window)
{
	// Convert the sketch of World1 to the game
	mapManager->convert_sketch(1,1, Enemies, Blocks, PowerUps, player);

    // Add enemies to the game with specific boundaries

    initGameEventMediator();
}

W1_LV1::~W1_LV1() {
  
}
