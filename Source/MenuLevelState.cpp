#include "Headers/MenuLevelState.h"

MenuLevelState::MenuLevelState(StateData* stateData) : MainMenuState(stateData)
{
    // Reinitialize buttons with level-specific content
    this->initButtons();
}

MenuLevelState::~MenuLevelState()
{
}

void MenuLevelState::initButtons()
{
    buttons.resize(4); // 3 levels + 1 back button

    float x = window->getSize().x / 2 - btn_Width / 2;
    float y = window->getSize().y / 2.2;

    buttons[BTN_LEVEL1] = new GUI::TextureButton( false,
        x, y, btn_Width, btn_Height,
        &font, "Level 1", btn_CharSize,
        sf::Color::Black, sf::Color::White, sf::Color::White,
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png"
    );

    y += btn_Height * 1.5;
    buttons[BTN_LEVEL2] = new GUI::TextureButton(false,
        x, y, btn_Width, btn_Height,
        &font, "Level 2", btn_CharSize,
        sf::Color::Black, sf::Color::White, sf::Color::White,
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png"
    );

    y += btn_Height * 1.5;
    buttons[BTN_LEVEL3] = new GUI::TextureButton(false,
        x, y, btn_Width, btn_Height,
        &font, "Level 3", btn_CharSize,
        sf::Color::Black, sf::Color::White, sf::Color::White,
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png"
    );

    y += btn_Height * 1.5;
    buttons[BTN_BACK] = new GUI::TextureButton(false,
        x, y, btn_Width, btn_Height,
        &font, "Back", btn_CharSize,
        sf::Color::Black, sf::Color::White, sf::Color::White,
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png"
    );
}

void MenuLevelState::updateGUI()
{
    for (auto& it : buttons)
    {
        it->update(mousePosWindow);
    }

    if (buttons[BTN_LEVEL1]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData);
        gameState->loadLevel(1); 
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL2]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData);
        gameState->loadLevel(1); 
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL3]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData);
        gameState->loadLevel(1); 
        this->states->push(gameState);
    }
    else if (buttons[BTN_BACK]->isPressed())
    {
        endState();
    }
}

void MenuLevelState::update(const float& dt)
{
    updateMousePosition();
    updateGUI();
}
