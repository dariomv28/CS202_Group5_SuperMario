#pragma once
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "LevelManager.h"
#include "stdafx.h"

class MapManager {
public:
    MapManager();
    ~MapManager();

    void loadMap(const std::string& mapName);  
    void update(float dt); 
    void render();  

    void setLevelManager(LevelManager* levelManager); 

private:
    LevelManager* levelManager; 
};

#endif // MAPMANAGER_H
