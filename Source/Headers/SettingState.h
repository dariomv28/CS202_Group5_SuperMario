#pragma once

#include "State.h"
#include "GUI.h"

namespace SettingMenu {
	enum Options { BTN_SOUND = 0, BTN_MUSIC, BTN_BACK };
}

class SettingState : public State
{
private:
    int nButtons;
    float btn_Width, btn_Height, btn_CharSize;

    sf::RectangleShape background;
    sf::Font font;

    std::vector<GUI::Button*> buttons;
    State* prevState;

    void initVariables();
    void initBackground();
    virtual void initButtons();
    void initFonts();

public:
    SettingState(StateData* stateData, State* prevState);
    virtual ~SettingState();

    virtual void updateGUI();
    virtual void update(const float& dt, const sf::Event& event);

    void renderGUI();
    void updateButtonPositions();
    void render(sf::RenderTarget* target);
    void updateBackground();
};