#pragma once

#include "State.h"
#include "LevelManager.h"
#include "DeathMenuState.h"
#include "PauseMenuState.h"


class MenuLevelState;

class GameState : public State {
private:
    LevelManager* levelManager;
    PauseMenuState* pauseMenu;
    DeathMenuState* deathMenu;

    int worldID, levelID;
    int strartPlayerHp;
public:
    GameState(StateData* stateData, int worldID, int levelID);
    virtual ~GameState();

    void reloadLevel();
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
    void renderLevelManager(sf::RenderTarget* target);

    void checkPause();
    void checkDeath();
    int getHealth() const;
    int getHealthStart() const;

    int getWorld() const;
    int getLevel() const;
};

