#include "Headers/W1_LV3.h"

W1_LV3::W1_LV3(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(1, 3, Enemies, Blocks, PowerUps, player);
	initGameEventMediator();

	Blocks.push_back(new MovingBlock(sf::Vector2f(4200.f, 200.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(4800.f, 200.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));

	Blocks.push_back(new MovingBlock(sf::Vector2f(7400.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(8000.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(8600.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(9200.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(9800.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
}

W1_LV3::~W1_LV3() {

}