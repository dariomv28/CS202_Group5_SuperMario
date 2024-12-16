#include "Headers/MenuLevelState.h"
#include "Headers/GameState.h"

MenuLevelState::MenuLevelState(StateData* stateData) : MainMenuState(stateData)
{
    // Reinitialize buttons with level-specific content
    this->initButtons();
    player = new Mario(sf::Vector2f(0.f, 0.f), sf::Vector2f(64.f, 64.f), 3.f, 50.f);
	//std::cerr << "im here" << std::endl;
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

void MenuLevelState::updateGUI(AudioSystem* audio)
{
    for (auto& it : buttons)
    {
        it->update(mousePosWindow);
    }

    // Keyboard navigation
    static int currentButtonIndex = 0;

    // Move selection up
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        // Prevent multiple rapid changes
        static sf::Clock keyTimer;
        if (keyTimer.getElapsedTime().asMilliseconds() > 150)
        {
            currentButtonIndex = (currentButtonIndex - 1 + buttons.size()) % buttons.size();
            keyTimer.restart();
        }
    }

    // Move selection down
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        // Prevent multiple rapid changes
        static sf::Clock keyTimer;
        if (keyTimer.getElapsedTime().asMilliseconds() > 150)
        {
            currentButtonIndex = (currentButtonIndex + 1) % buttons.size();
            keyTimer.restart();
        }
    }

    for (size_t i = 0; i < buttons.size(); ++i)
    {
        if (i == currentButtonIndex)
        {
            buttons[i]->highlight(true);
        }
    }

    // Add a static flag to track key state
    static bool enterReleased = false;

    // Select button with Enter or Space
    if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
        sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) &&
        enterReleased)
    {
        // Reset the enter released flag
        enterReleased = false;

        // Simulate button press for the currently selected button
        if (currentButtonIndex == BTN_LEVEL1)
        {
            GameState* gameState = new GameState(this->stateData);
            gameState->loadLevel(player, 1, 1);
            this->states->push(gameState);
            audio->playLevel1Music();
        }
        else if (currentButtonIndex == BTN_LEVEL2)
        {
            GameState* gameState = new GameState(this->stateData);
            gameState->loadLevel(player, 1, 2);
            this->states->push(gameState);
            audio->playLevel2Music();
        }
        else if (currentButtonIndex == BTN_LEVEL3)
        {
            GameState* gameState = new GameState(this->stateData);
            gameState->loadLevel(player, 1, 3);
            this->states->push(gameState);
            audio->playLevel3Music();
        }
        else if (currentButtonIndex == BTN_BACK)
        {
            endState();
        }
    }

    // Reset the flag when the key is released
    if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
        !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        enterReleased = true;
    }

    // Existing mouse press handlers
    if (buttons[BTN_LEVEL1]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData);
        gameState->loadLevel(player, 1, 1);
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL2]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData);
        gameState->loadLevel(player, 1, 2);
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL3]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData);
        gameState->loadLevel(player, 1, 3);
        this->states->push(gameState);
    }
    else if (buttons[BTN_BACK]->isPressed())
    {
        endState();
    }
}

void MenuLevelState::update(const float& dt, AudioSystem* audio)
{
    updateMousePosition();
    updateGUI(audio);
}
