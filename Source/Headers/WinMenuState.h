#pragma once
#include "State.h"

class GameState;

class WinMenuState: public State
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
    WinMenuState(StateData* stateData, GameState* gameState);
    virtual ~WinMenuState();

    void updateGUI();
    void update(const float& dt, const sf::Event& event);
    void render(sf::RenderTarget* target);
};

