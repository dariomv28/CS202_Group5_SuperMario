#pragma once
#include "State.h"
#include "GUI.h"

class EnterNameState : public State {
private:
    sf::Font font;
    sf::Text promptText;
    sf::Text inputText;
    std::string userInput;

    sf::RectangleShape inputBox;
    GUI::TextButton* confirmButton;
    GUI::TextButton* cancelButton;


    void initFonts();
    void initText();
    void initButtons();
    void initInputBox();

public:
    EnterNameState(StateData* stateData);
    virtual ~EnterNameState();

    void updateInput(const sf::Event& event);
    void updateGUI();
    void update(const float& dt, const sf::Event& event) override;
    void render(sf::RenderTarget* target) override;
};
