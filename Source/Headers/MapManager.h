#pragma once
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "LevelManager.h"
#include "stdafx.h"
#include "Enemy.h"
#include "Mario.h"
#include "Block.h"

class MapManager {
public:
    MapManager();
    ~MapManager();

    void loadMap(const std::string& mapName, Mario* &Player, vector<Enemy*>& Enemies, vector<Block*>& Blocks, sf::RenderWindow *window);  
    void update(float dt, Mario* Player); 
    void render();  

    void setLevelManager(LevelManager* levelManager); 


private:
    LevelManager* levelManager; 
    


};
#pragma once

//void draw_map(unsigned i_view_x, const sf::Image& i_map_sketch, sf::RenderWindow& i_window, const sf::Texture& i_map_texture, const Map& i_map);
#endif // MAPMANAGER_H
