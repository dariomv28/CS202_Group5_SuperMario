#include "Headers/MenuLevelState.h"
#include "Headers/GameState.h"

MenuLevelState::MenuLevelState(StateData* stateData, int world) : MainMenuState(stateData),level(0)
{
    // Reinitialize buttons with level-specific content
    this->world = world;
    this->initButtons();
    player = new Mario(sf::Vector2f(0.f, 0.f), sf::Vector2f(64.f, 64.f), 3.f, 30.f);
}

MenuLevelState::~MenuLevelState()
{
}

void MenuLevelState::initButtons()
{
    buttons.resize(4); // 3 levels + 1 back button

    float x = window->getSize().x / 2 - btn_Width / 2;
    float y = window->getSize().y / 2.2;

    // Init World text
    worldText.setFont(font);
    worldText.setString("world " + std::to_string(world));
    worldText.setCharacterSize(30);
    worldText.setFillColor(sf::Color::Black);
    worldText.setPosition(SCREEN_WIDTH/2 - worldText.getGlobalBounds().width/2, y - worldText.getGlobalBounds().height*2);

    //y += btn_Height * 1.5;


    buttons[BTN_LEVEL1] = new GUI::TextureButton( false,
        x, y, btn_Width, btn_Height,
        &font,  "Level 1", btn_CharSize,
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
        static sf::Clock keyTimer;
        if (keyTimer.getElapsedTime().asMilliseconds() > 150)
        {
            // Reset the enter released flag
            enterReleased = false;

            // Simulate button press for the currently selected button
            if (currentButtonIndex == BTN_LEVEL1)
            {
                this->stateData->audio->playbuttonSound();
                GameState* gameState = new GameState(this->stateData, this);
                this->setLevel(1);
                gameState->loadLevel(player, world, level);
                this->states->push(gameState);

            }
            else if (currentButtonIndex == BTN_LEVEL2)
            {
                this->stateData->audio->playbuttonSound();
                GameState* gameState = new GameState(this->stateData, this);
                this->setLevel(2);
                gameState->loadLevel(player, world, level);
                this->states->push(gameState);

            }
            else if (currentButtonIndex == BTN_LEVEL3)
            {
                this->stateData->audio->playbuttonSound();
                GameState* gameState = new GameState(this->stateData, this);
                this->setLevel(3);
                gameState->loadLevel(player, world, level);
                this->states->push(gameState);

            }
            else if (currentButtonIndex == BTN_BACK)
            {
                this->stateData->audio->playbuttonSound();
                endState();
            }
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
        GameState* gameState = new GameState(this->stateData, this);
        this->setLevel(1);
        gameState->loadLevel(player, world, level);
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL2]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData, this);
        this->setLevel(2);
        gameState->loadLevel(player, world, level);
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL3]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData, this);

        this->setLevel(3);
        gameState->loadLevel(player, world, level);
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

void MenuLevelState::render(sf::RenderTarget* target)
{
    if (!target)
	{
		target = window;
	}
    target->draw(background);
	target->draw(worldText);
	for (auto& it : buttons)
	{
		it->render(target);
	}
}


int MenuLevelState::getWorld() const {
    std::cout << "World value: " << world << ", address = " << this << std::endl;
    return this->world;
}

void MenuLevelState::setWorld(int newWorld) {
    this->world = newWorld;
    std::cout << "setWorld called: world = " << this->world << ", address = " << this << std::endl;
}

int MenuLevelState::getLevel() const {
    std::cout << "Level value: " << level << ", address = " << this << std::endl;
    return this->level;
}

void MenuLevelState::setLevel(int newLevel) {
    this->level = newLevel;
    std::cout << "setLevel called: level = " << this->level << ", address = " << this << std::endl;
}

PlayerManager* MenuLevelState::getPlayer() const {
    std::cout << "Player address MenuLevelState: " << player << std::endl;
    return this->player;
}

int MenuLevelState::getHealth() {
    return player->getHealth();

}

void MenuLevelState::setPlayerHealth(int newHealth) {
    if (player) {
        player->setHealth(newHealth);
    }
}