#pragma once
#include "State.h"
class GameState :
    public State
{
private:

public:
    GameState(StateData* stateData);
    virtual ~GameState();

    // Functions

    void endState();
    
    void updateKeyBinds(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

