#pragma once
#include "State.h"
#include <SFML/Graphics.hpp>

class MenuCharacterSelectionState : public State
{
private:

    sf::Texture marioTexture;
    sf::Texture luigiTexture;
    sf::Sprite characterSprite;
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;


    sf::RectangleShape selectionBox;
    void initBackground();


    sf::Font font;
    sf::Text title;


    int currentCharacterIndex;

    void initTextures();
    void initSprites();
    void initFonts();
    void initTitle();
    void initSelectionBox();

public:
    MenuCharacterSelectionState(StateData* stateData);
    virtual ~MenuCharacterSelectionState();

    void updateInput();
    void update(const float& dt) override;
    void render(sf::RenderTarget* target = nullptr) override;
};
