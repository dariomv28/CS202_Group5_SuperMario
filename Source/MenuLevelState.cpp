#include "Headers/MenuLevelState.h"
#include "Headers/GameState.h"
#include "Headers/FireBuff.h"

MenuLevelState::MenuLevelState(StateData* stateData, int world) : MainMenuState(stateData),level(0)
{
    // Reinitialize buttons with level-specific content
    this->world = world;
    this->initButtons();
    player = new Mario(sf::Vector2f(0.f, 0.f), sf::Vector2f(64.f, 64.f), 3.f, 30.f);
    player->addBuff(new FireBuff());
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
    worldText.setCharacterSize(50);
    worldText.setFillColor(sf::Color::Cyan);
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