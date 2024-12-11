#pragma once
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "MapManager.h"
#include "stdafx.h"
#include "Enemy.h"
#include "Mario.h"
#include "Block.h"
#include "PowerUpObject.h"

class LevelManager {
protected:
    MapManager* mapManager;
    sf::RenderWindow* window;
public:
    LevelManager(sf::RenderWindow* window);
    virtual void update(PlayerManager* Player, const float& dt);
    virtual void render();

};
#pragma once

#endif // MAPMANAGER_H
