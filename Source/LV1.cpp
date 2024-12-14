#include "Headers/LV1.h"

#include <iostream>


LV1::LV1(PlayerManager* player, sf::RenderWindow *window):
	LevelManager(player, window)
{
	// Convert the sketch of World1 to the game
	mapManager->convert_sketch(1, Enemies, Blocks, PowerUps, player);

    // Add enemies to the game with specific boundaries

	Enemies.push_back(new Koopa(sf::Vector2f(700.f, 500.f), sf::Vector2f(64.f, 64.f)));


    initGameEventMediator();
}

LV1::~LV1() {
  
}
