#pragma once
#include "State.h"

namespace PauseMenu {
    enum Options { BTN_CONTINUE = 0, BTN_SAVEGAME, BTN_SETTING, BTN_MAINMENU };
}

class GameState;

class PauseMenuState : public State
{
protected:
    int nButtons;
    float btn_Width, btn_Height, btn_CharSize;

    sf::RectangleShape background;
    sf::Font font;

    std::vector<GUI::Button*> buttons;
    GameState* gameState;

    void initVariables();
    void initBackground();
    virtual void initButtons();
    void initFonts();

public:
    PauseMenuState(StateData* stateData, GameState* gameState);
    virtual ~PauseMenuState();

    virtual void updateGUI();
    virtual void update(const float& dt, const sf::Event& event);

    void renderGUI();
    void updateButtonPositions();
    void render(sf::RenderTarget* target);
    void updateBackground();
};
