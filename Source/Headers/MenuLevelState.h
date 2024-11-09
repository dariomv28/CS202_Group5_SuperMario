#pragma once
#include "MainMenuState.h"

enum level_options { BTN_LEVEL1 = 0, BTN_LEVEL2, BTN_LEVEL3, BTN_BACK };

class MenuLevelState : public MainMenuState
{
private:
    void initButtons() override;

public:
    MenuLevelState(StateData* stateData);
    virtual ~MenuLevelState();

    void updateGUI() override;
    void update(const float& dt) override;
};
