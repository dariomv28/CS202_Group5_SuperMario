#include "Headers/W3_LV3.h"
#include "Headers/Bowser.h"

W3_LV3::W3_LV3(PlayerManager* player, sf::RenderWindow* window):
	LevelManager(player, window) 
{
	mapManager->convert_sketch(3,3, Enemies, Blocks, PowerUps, player);

	Enemies.push_back(new Bowser(sf::Vector2f(500.f, 250.f), sf::Vector2f(128.f, 140.f), 374.f, 1120.f));

	initGameEventMediator();
}

W3_LV3::~W3_LV3() {

}

void W3_LV3::update(const float& dt) {
	LevelManager::update(dt);
}

void W3_LV3::render(sf::RenderTarget* target) {
	LevelManager::render(target);
}

