#pragma once
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "MapManager.h"
#include "stdafx.h"
#include "Enemy.h"
#include "Mario.h"
#include "Block.h"
#include "PowerUpObject.h"
#include "LevelGUI.h"
#include "GameEventMediator.h"
#include "PhysicsEngine.h"
#include "AudioSystem.h"

class LevelManager {
protected:
    MapManager* mapManager;
    sf::RenderWindow* window;
    PlayerManager* player;
    vector<Enemy*> Enemies;
    vector<Block*> Blocks;
    vector<PowerUpObject*> PowerUps;
    LevelGUI* levelGUI;
    GameEventMediator* eventMediator;
    PhysicsEngine* physicsEngine;
    AudioSystem* audio;
public:
    LevelManager(PlayerManager* player, sf::RenderWindow* window);
    virtual ~LevelManager();
    void initGameEventMediator();
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target = nullptr);

};
#pragma once

#endif // MAPMANAGER_H
 