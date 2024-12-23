#pragma once
#include "State.h"

namespace DeathMenu {
    enum Options { BTN_YES = 0, BTN_NO };
}

class GameState;

class DeathMenuState : public State
{
protected:
    sf::Font font;

    sf::Text titleText;
    sf::Text questionText;
    sf::Text yesButtonText;
    sf::Text noButtonText;

   
    sf::RectangleShape background;

    GameState* gameState;

    void initVariables();
    void initBackground();
    void initTexts();
    void centerText(sf::Text& text, float y);
   
    void updateBackground();
    void updateButtonHover(sf::Text& text, sf::Vector2f mousePos);

public:
    DeathMenuState(StateData* stateData, GameState* gameState);
    virtual ~DeathMenuState();

    void updateGUI();
    void update(const float& dt, const sf::Event& event);
    void render(sf::RenderTarget* target);
};


