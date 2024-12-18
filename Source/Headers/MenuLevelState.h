#pragma once
#include "MainMenuState.h"
#include "PlayerManager.h"

enum level_options { BTN_LEVEL1 = 0, BTN_LEVEL2, BTN_LEVEL3, BTN_BACK };

class MenuLevelState : public MainMenuState
{
private:
    int world;
    sf::Text worldText;
    void initButtons() override;
    PlayerManager* player;
public:
    MenuLevelState(StateData* stateData, int world);
    virtual ~MenuLevelState();

    void updateGUI() override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
};
