#include "Headers/MapManager.h"
#include "Headers/LV1.h"
#include "Headers/LV2.h"
#include "Headers/LV3.h"
#include <iostream>

MapManager::MapManager() : levelManager(nullptr) {
    // Constructor
}

MapManager::~MapManager() {
    // Destructor
    delete levelManager;
}

void MapManager::loadMap(const std::string& mapName)
{
    std::cout << "Loading map: " << mapName << std::endl;

    if (mapName == "Level1_Map") {
        levelManager = new LV1();  
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

void MapManager::update(float dt) {
    if (levelManager) {
        levelManager->update(dt);
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
