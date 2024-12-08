#pragma once
#include "State.h"
#include "MapManager.h"
#include "Mario.h"
#include "Enemy.h"
#include "PhysicsEngine.h"
#include "Block.h"
#include "stdafx.h"
#include "LevelGUI.h"
#include "GameEventMediator.h"
#include "Goomba.h"
#include "PowerUpObject.h"

class GameState : public State {
private:
    GameEventMediator* eventMediator;
    PhysicsEngine* physicsEngine;
    MapManager* mapManager;
    Mario* player;
	vector<Enemy*> Enemies;
	vector<Block*> Blocks;
   	vector<PowerUpObject*> PowerUps;
    LevelGUI* levelGUI;      
public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void initGameEventMediator();
    void loadLevel(int levelID);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

