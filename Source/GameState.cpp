#include "Headers/GameState.h"
#include "Headers/W1_LV1.h"
#include "Headers/W2_LV1.h"
#include "Headers/W3_LV1.h"
#include "Headers/W1_LV2.h"
#include "Headers/W1_LV3.h"
#include "Headers/W2_LV2.h"
#include "Headers/W2_LV3.h"

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
    std::string worldLevel = "W" + std::to_string(worldID) + "_LV" + std::to_string(level);
    if (worldLevel == "W1_LV1") {
		levelManager = new W1_LV1(player, window);
    }
    else if (worldLevel == "W1_LV2") {
        levelManager = new W1_LV2(player, window);
    } 	
    else if (worldLevel == "W1_LV3") {
		levelManager = new W1_LV3(player, window);
	}
    else if (worldLevel == "W2_LV1") {
		levelManager = new W2_LV1(player, window);
    }
    else if (worldLevel == "W2_LV2") {
        levelManager = new W2_LV2(player, window);
    }
	else if (worldLevel == "W2_LV3") {
        levelManager = new W2_LV3(player, window);
    }
    else if (worldLevel == "W3_LV1") {
		levelManager = new W3_LV1(player, window);
	}
    else if (worldLevel == "W3_LV2") {
		//	levelManager = new W3_LV2(player, window);
	}
	else if (worldLevel == "W3_LV3") {
		//	levelManager = new W3_LV3(player, window);
	}
	else {
		cerr << "Invalid level" << endl;
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

