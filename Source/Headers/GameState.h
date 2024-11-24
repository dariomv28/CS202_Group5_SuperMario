#pragma once
#include "State.h"
#include "MapManager.h"
#include "Mario.h"
#include "Enemy.h"
#include "PhysicsEngine.h"
#include "Block.h"
#include "stdafx.h"

class GameState : public State {
private:
    PhysicsEngine physicsEngine;
    MapManager* mapManager;
    std::vector<GameObject*> gameObjects;
    Mario* player;
	vector<Enemy*> Enemies;
	vector<Block*> Blocks;
public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void loadLevel(int levelID);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

