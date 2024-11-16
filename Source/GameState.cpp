#include "Headers/GameState.h"

GameState::GameState(StateData* stateData) : State(stateData), mapManager(nullptr) {
    mario = new Mario();
    mario->init();
	//loadLevel(1);
}


GameState::~GameState() {
    delete mapManager;
}

void GameState::loadLevel(int level)
{
    MapManager* mapManager = new MapManager();

    if (level == 1) {
        mapManager->loadMap("Level1_Map");
    }
    else if (level == 2) {
        mapManager->loadMap("Level2_Map"); 
    }
    else if (level == 3) {
        mapManager->loadMap("Level3_Map"); 
    }

    this->mapManager = mapManager;
}

void GameState::update(const float& dt) {
    mapManager->update(dt);
}

void GameState::render(sf::RenderTarget* target) {
    if (!target) {
		target = window;
	}
    mapManager->render();
    mario->render(target);
}

