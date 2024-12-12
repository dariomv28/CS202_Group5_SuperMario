#pragma once
#include "State.h"
#include "LevelManager.h"
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
    LevelManager* levelManager;
public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void loadLevel(PlayerManager* player, int worldID, int levelID);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

