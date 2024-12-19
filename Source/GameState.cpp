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

GameState::GameState(StateData* stateData, MenuLevelState* menuLevelState)
    : State(stateData), levelManager(nullptr), menuLevelState(menuLevelState) {}


GameState::~GameState() {
    delete levelManager;
}

void GameState::loadLevel(PlayerManager* player, int worldID, int level) {
    if (levelManager) {
        delete levelManager;
    }
    if (menuLevelState) {
        this->strartPlayerHp = menuLevelState->getHealth();
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
		levelManager = new W3_LV2(player, window);
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
    // cerr << player->hitbox.getPosition().x << endl;
	// cerr << Blocks.size() << endl;
}

void GameState::renderLevelManager(sf::RenderTarget* target) {
    if (this->levelManager)
        this->levelManager->render(target);
}

int GameState::getHealth() const
{

    return menuLevelState->getHealth();

}

int GameState::getHealthStart() const
{

    return this->strartPlayerHp;


}

void GameState::checkPause() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        this->states->push(new PauseMenuState(this->stateData, this));
    }
}

void GameState::checkDeath() {

    if (this->getHealth() <= 0) {
        this->states->push(new DeathMenuState(this->stateData, this));
    }
}

int GameState::getWorld() const {
    return this->menuLevelState->getWorld();
}

int GameState::getLevel() const {
    return this->menuLevelState->getLevel();
}

PlayerManager* GameState::getPlayer() const {
    std::cout << "Player address GameState: " << menuLevelState->getPlayer() << std::endl;
    return this->menuLevelState->getPlayer();
}

void GameState::setPlayerHealth(int newHealth) {
    if (menuLevelState) {
        menuLevelState->setPlayerHealth(newHealth);
    }
}
