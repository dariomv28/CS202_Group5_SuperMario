#pragma once
#include "State.h"
#include "MapManager.h"

class GameState : public State {
private:
    MapManager* mapManager;
public:
    GameState(StateData* stateData);
    virtual ~GameState();

    void loadLevel(int levelID);
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};

