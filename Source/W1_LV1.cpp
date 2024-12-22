#include "Headers/W1_LV1.h"
#include <iostream>


W1_LV1::W1_LV1(PlayerManager* player, sf::RenderWindow *window):
	LevelManager(player, window)
{
	// Convert the sketch of World1 to the game
	mapManager->convert_sketch(1,1, Enemies, Blocks, PowerUps, player);

    // Add enemies to the game with specific boundaries

	Enemies.push_back(new Koopa(sf::Vector2f(700.0f, 500.0f), sf::Vector2f(64.f, 64.f)));

    MovingBlock* block = new MovingBlock(
        sf::Vector2f(300.f, 100.f),    // Initial position
        sf::Vector2f(64.f, 64.f),      // Size
        "basic_ground_single",          // Texture name
        100.f,                         // Movement speed
        300.f                          // Movement distance
    );

	Blocks.push_back(block);

    initGameEventMediator();
}

W1_LV1::~W1_LV1() {
  
}
