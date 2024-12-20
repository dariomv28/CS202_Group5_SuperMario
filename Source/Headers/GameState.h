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
    MenuLevelState* menuLevelState;

    int strartPlayerHp;
public:
    GameState(StateData* stateData, MenuLevelState* menuLevelState);
    virtual ~GameState();

    void loadLevel(PlayerManager* player, int worldID, int levelID);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
    void renderLevelManager(sf::RenderTarget* target);

    void checkPause();
    void checkDeath();
    int getHealth() const;
    int getHealthStart() const;
    void setPlayerHealth(int newHealth);

    int getWorld() const;
    int getLevel() const;
    PlayerManager* getPlayer() const;
};

