#pragma once
#include "MainMenuState.h"

enum world_options { BTN_WORLD1 = 0, BTN_WORLD2, BTN_WORLD3, BTN_BACKTOMAIN };

class MenuWorldState :
    public MainMenuState
{
private:
    int world;
	bool Continue;
    void initButtons() override;
public:
    MenuWorldState(StateData* stateData);
    MenuWorldState(StateData* stateData, bool Continue);
    virtual ~MenuWorldState();

    void updateGUI() override;
    void update(const float& dt) override;
    void render(sf::RenderTarget* target) override;
};

