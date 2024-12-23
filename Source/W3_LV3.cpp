#include "Headers/W3_LV3.h"

W3_LV3::W3_LV3(PlayerManager* player, sf::RenderWindow* window):
	LevelManager(player, window) 
{
	mapManager->convert_sketch(3,3, Enemies, Blocks, PowerUps, player);

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

