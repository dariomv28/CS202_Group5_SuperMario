#pragma once

#include "State.h"
#include "LevelManager.h"
#include "DeathMenuState.h"
#include "PauseMenuState.h"
#include "WinMenuState.h"

class GameState : public State {
private:
    LevelManager* levelManager;
    PauseMenuState* pauseMenu;
    DeathMenuState* deathMenu;

    WinMenuState* winMenu;

    PlayerManager* clonePlayer;

    int worldID, levelID;
public:
    GameState(StateData* stateData, int worldID, int levelID);
    virtual ~GameState();

    void reloadLevel();
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
    void renderLevelManager(sf::RenderTarget* target);

    void saveGame();

    void checkPause();
    void checkDeath();
    void checkWin();


    int getWorld() const;
    int getLevel() const;
};

