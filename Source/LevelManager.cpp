#include "Headers/LevelManager.h"

LevelManager::LevelManager(sf::RenderWindow* window) {
	this->window = window;
	mapManager = new MapManager(window);
}

void LevelManager::update(PlayerManager* Player, const float& dt) {
	if (mapManager) {
		//levelManager->update(dt);
		mapManager->update(Player, window);
	}
}


void LevelManager::render() {
	mapManager->draw_map(window);

	//this->draw_map(false, false, view_x, *window);
}

//MapManager::MapManager() : levelManager(nullptr) {
//    // Constructor
//}

