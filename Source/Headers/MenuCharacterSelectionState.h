#pragma once

#include "State.h"

class MenuCharacterSelectionState : public State {
private:
    // Resources
    sf::Texture marioTexture;
    sf::Texture luigiTexture;
    sf::Texture backgroundTexture;
    sf::Texture frameTexture;
    sf::Font font;

    // UI Elements
    sf::Sprite backgroundSprite;
    struct CharacterCard {
        sf::RectangleShape card;
        sf::Sprite characterSprite;
        sf::Text nameText;
        sf::Text descriptionText;
        bool isSelected;
        float scale;
        sf::Vector2f originalPos;
    };
    std::vector<CharacterCard> characterCards;

    // Animation
    float animationTime;
    float cardHoverScale;
    float cardNormalScale;

    // Selection
    int currentCharacterIndex;
    bool transitioningOut;
    float transitionAlpha;

    // UI Components
    sf::Text title;
    sf::RectangleShape selectionIndicator;
    sf::Text promptText;

    // Initialization functions
    void initTextures();
    void initBackground();
    void initFont();
    void initCharacterCards();
    void initUI();

    // Animation helpers
    void updateCardAnimations(const float& dt);
    void updateTransitionEffect(const float& dt);

public:
    MenuCharacterSelectionState(StateData* stateData);
    virtual ~MenuCharacterSelectionState();

    void updateInput();
    void update(const float& dt);
    void render(sf::RenderTarget* target);
};