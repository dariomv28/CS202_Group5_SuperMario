#include "Headers/GameState.h"
#include "Headers/LV1.h"
#include "Headers/LV2.h"
#include "Headers/LV3.h"

GameState::GameState(StateData* stateData) : State(stateData), levelManager(nullptr) {
    
}


GameState::~GameState() {
    // Clean up all game objects
    delete levelManager;
}

void GameState::loadLevel(PlayerManager* player, int worldID, int level) {
    if (levelManager) {
        delete levelManager;
    }

    switch (level) {
        case 1:
		    levelManager = new LV1(player, window);
		    break;
        case 2:
            levelManager = new LV2(player, window);
			break;
        case 3:
            levelManager = new LV3(player, window);
			break;
    }
 
}


void GameState::update(const float& dt) {
    if (levelManager) {
		levelManager->update(dt);
    }
 
}
  
void GameState::render(sf::RenderTarget* target) {
    if (!target) {
        target = window;
    }

    if (levelManager) {
        levelManager->render();
    }
    // cerr << player->hitbox.getPosition().x << endl;
	// cerr << Blocks.size() << endl;
}

