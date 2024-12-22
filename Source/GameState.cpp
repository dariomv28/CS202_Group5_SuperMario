#include "Headers/GameState.h"
#include "Headers/MenuLevelState.h"
#include "Headers/W1_LV1.h"
#include "Headers/W2_LV1.h"
#include "Headers/W3_LV1.h"
#include "Headers/W1_LV2.h"
#include "Headers/W1_LV3.h"
#include "Headers/W2_LV2.h"
#include "Headers/W2_LV3.h"
#include "Headers/W3_LV2.h"
#include "Headers/W3_LV3.h"

GameState::GameState(StateData* stateData, int worldID, int levelID)
    : State(stateData), levelManager(nullptr), worldID(worldID), levelID(levelID) {}


GameState::~GameState() {
    delete levelManager;
}

void GameState::reloadLevel() {
    if (levelManager) {
        delete levelManager;
    }

    std::string worldLevel = "W" + std::to_string(worldID) + "_LV" + std::to_string(levelID);
    if (worldLevel == "W1_LV1") {
		levelManager = new W1_LV1(this->stateData->userData->getPlayer(worldID), window);
    }
    else if (worldLevel == "W1_LV2") {
        levelManager = new W1_LV2(this->stateData->userData->getPlayer(worldID), window);
    } 	
    else if (worldLevel == "W1_LV3") {
		levelManager = new W1_LV3(this->stateData->userData->getPlayer(worldID), window);
	}
    else if (worldLevel == "W2_LV1") {
		levelManager = new W2_LV1(this->stateData->userData->getPlayer(worldID), window);
    }
    else if (worldLevel == "W2_LV2") {
        levelManager = new W2_LV2(this->stateData->userData->getPlayer(worldID), window);
    }
	else if (worldLevel == "W2_LV3") {
        levelManager = new W2_LV3(this->stateData->userData->getPlayer(worldID), window);
    }
    else if (worldLevel == "W3_LV1") {
		levelManager = new W3_LV1(this->stateData->userData->getPlayer(worldID), window);
	}
    else if (worldLevel == "W3_LV2") {
		levelManager = new W3_LV2(this->stateData->userData->getPlayer(worldID), window);
	}
	else if (worldLevel == "W3_LV3") {
		levelManager = new W3_LV3(this->stateData->userData->getPlayer(worldID), window);
	}
	else {
		cerr << "Invalid level" << endl;
	}
 
}


void GameState::update(const float& dt) {
    if (levelManager) {
		levelManager->update(dt);
    }
    checkPause();
    checkDeath();
 
}
  
void GameState::render(sf::RenderTarget* target) {
    if (!target) {
        target = window;
    }

    if (levelManager) {
        levelManager->render();
    }
}

void GameState::renderLevelManager(sf::RenderTarget* target) {
    if (this->levelManager)
        this->levelManager->render(target);
}


void GameState::checkPause() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->states->push(new PauseMenuState(this->stateData, this));
    }
}

void GameState::checkDeath() {
	if (this->stateData->userData->getPlayer(worldID)->getHealth() <= 0) {
		this->states->push(new DeathMenuState(this->stateData, this));
	}
}

int GameState::getWorld() const {
	return this->worldID;
}

int GameState::getLevel() const {
	return this->levelID;
}



