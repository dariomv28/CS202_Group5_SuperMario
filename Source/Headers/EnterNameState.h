#ifndef ENTERNAMESTATE_H
#define ENTERNAMESTATE_H

#include "State.h"
#include "GUI.h"

class EnterNameState : public State {
private:
    // Resources
    sf::Font font;

    // Background
    sf::Color backgroundColor;

    // Text
    sf::Text promptText;
    sf::Text inputText;
    std::string userInput;

    // GUI elements
    sf::RectangleShape inputBox;
    GUI::TextButton* confirmButton;
    GUI::TextButton* cancelButton;

    // Decorative elements
    sf::CircleShape coinShape;
    sf::CircleShape coinShape2;
    float animationTime;

    // Initializer functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initText();
    void initInputBox();
    void initButtons();
    void initDecorations();

public:
    EnterNameState(StateData* state_data);
    virtual ~EnterNameState();

    // Functions
    void updateInput(const sf::Event& event);
    void updateButtons();
    void updateAnimation(const float& dt);

    virtual void endState();
    virtual void update(const float& dt, const sf::Event& event);
    virtual void render(sf::RenderTarget* target = nullptr);
};

#endif // ENTERNAMESTATE_H