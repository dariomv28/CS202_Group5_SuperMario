#include "Headers/MapManager.h"
#include "Headers/LV1.h"
#include "Headers/LV2.h"
#include "Headers/LV3.h"
#include <iostream>

#include <array>
#include <chrono>
#include <cmath>
//#include <SFML/Graphics.hpp>
//#include "Headers/stdafx.h"
using namespace std;
//#include "Headers/Animation.hpp"
//#include "Headers/Global.hpp"

MapManager::MapManager() : levelManager(nullptr) 
{

}



//MapManager::MapManager() : levelManager(nullptr) {
//    // Constructor
//}

MapManager::~MapManager() {
    // Destructor
    delete levelManager;
}

void MapManager::loadMap(const std::string& mapName, Mario* &Player, vector<Enemy*>& Enemies, vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, sf::RenderWindow *window)
{
    std::cout << "Loading map: " << mapName << std::endl;

    if (mapName == "Level1_Map") {
        levelManager = new LV1(Player, Enemies, Blocks, PowerUp, window);
    }
    else if (mapName == "Level2_Map") {
        levelManager = new LV2();  
    }
    else if (mapName == "Level3_Map") {
        levelManager = new LV3();  
    }

    if (levelManager) {
        levelManager->loadLevel();
    }
}

void MapManager::update(float dt, Mario* Player) {
    if (levelManager) {
        //levelManager->update(dt);
        levelManager->update(Player);
    }
}

void MapManager::render() {
    if (levelManager) {
        levelManager->render();
    }
}

void MapManager::setLevelManager(LevelManager* newLevelManager) {
    levelManager = newLevelManager;
}
