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
    if (clonePlayer) {
		delete clonePlayer;
	}
    
    clonePlayer = this->stateData->userData->getClonePlayer(worldID);

    std::string worldLevel = "W" + std::to_string(worldID) + "_LV" + std::to_string(levelID);
    if (worldLevel == "W1_LV1") {
		levelManager = new W1_LV1(clonePlayer, window);
    }
    else if (worldLevel == "W1_LV2") {
        levelManager = new W1_LV2(clonePlayer, window);
    } 	
    else if (worldLevel == "W1_LV3") {
		levelManager = new W1_LV3(clonePlayer, window);
	}
    else if (worldLevel == "W2_LV1") {
		levelManager = new W2_LV1(clonePlayer, window);
    }
    else if (worldLevel == "W2_LV2") {
        levelManager = new W2_LV2(clonePlayer, window);
    }
	else if (worldLevel == "W2_LV3") {
        levelManager = new W2_LV3(clonePlayer, window);
    }
    else if (worldLevel == "W3_LV1") {
		levelManager = new W3_LV1(clonePlayer, window);
	}
    else if (worldLevel == "W3_LV2") {
		levelManager = new W3_LV2(clonePlayer, window);
	}
	else if (worldLevel == "W3_LV3") {
		levelManager = new W3_LV3(clonePlayer, window);
	}
    //else if (worldID == 4)
    //{
    //    // Continue state
    //    std::ifstream saveFile("SaveGame.txt");
    //    int currentWorld;
    //    int currentLevel;
    //    saveFile >> currentWorld;
    //    saveFile >> currentLevel;
    //    saveFile.close();

    //    levelManager = new W4(this->stateData->userData->getPlayer(currentWorld), window);
    //}
	else {
		cerr << "Invalid level" << endl;
	}
 
}

void GameState::update(const float& dt) {
    std::cout << getQuit() << '\n';
    if (levelManager) {
		levelManager->update(dt);
    }
    checkPause();
    checkDeath();
    checkWin();
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
	if (clonePlayer->getHealth() <= 0) {
		this->states->push(new DeathMenuState(this->stateData, this));
	}
}

void GameState::saveGame() {
    ///Set the current state to userData 
    //Set player

    PlayerManager* player = this->stateData->userData->getPlayer(worldID);
    delete player;
    this->stateData->userData->setPlayer(worldID, clonePlayer);

    //Set the level as completed and set the score
    this->stateData->userData->setCompleted(worldID, levelID);
    this->stateData->userData->setScore(worldID, levelID, levelManager->getScore());

    //Save the data
}

void GameState::checkWin() {
    if (clonePlayer->getPosition().x > 1000000) {
        saveGame();
        this->states->push(new WinMenuState(this->stateData, this));


	}
}

int GameState::getWorld() const {
	return this->worldID;
}

int GameState::getLevel() const {
	return this->levelID;
}



