#include "Headers/PauseMenuState.h"
#include "Headers/MainMenuState.h"
#include "Headers/GUI.h"
#include "Headers/GameState.h"

void PauseMenuState::initVariables()
{
    nButtons = 2;
    btn_Width = 400;
    btn_Height = 75;
    btn_CharSize = 20;
}

void PauseMenuState::initBackground()
{
    background.setSize(sf::Vector2f(window->getSize().x, window->getSize().y));
    background.setFillColor(sf::Color(0, 0, 0, 150));
}

void PauseMenuState::initFonts()
{
    if (!font.loadFromFile("Source/Resources/font/Super-Mario-Bros--3.ttf")) {
        throw("ERROR::PAUSEMENUSTATE::COULD NOT LOAD FONT");
    }
}

void PauseMenuState::initButtons()
{
    buttons.resize(nButtons);

    float x = window->getSize().x / 2 - btn_Width / 2;
    float y = window->getSize().y / 2.2;

    buttons[PauseMenu::BTN_CONTINUE] = new GUI::TextureButton(false,
        x, y, btn_Width, btn_Height,
        &font, "Continue", btn_CharSize,
        sf::Color::Black, sf::Color::White, sf::Color::White,
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png"
    );

    y += btn_Height * 1.5;
    buttons[PauseMenu::BTN_MAINMENU] = new GUI::TextureButton(false,
        x, y, btn_Width, btn_Height,
        &font, "Main Menu", btn_CharSize,
        sf::Color::Black, sf::Color::White, sf::Color::White,
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png",
        "Source/Resources/texture/menu_button.png"
    );
}

PauseMenuState::PauseMenuState(StateData* stateData, GameState* gameState)
    : State(stateData), gameState(gameState)
{
    initVariables();
    initBackground();
    initFonts();
    initButtons();
}

PauseMenuState::~PauseMenuState()
{
    for (auto it = buttons.begin(); it != buttons.end(); ++it)
    {
        delete* it;
    }
}

void PauseMenuState::updateGUI()
{
    sf::Vector2f mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

    for (auto& it : buttons)
    {
        it->update(static_cast<sf::Vector2i>(mousePosView));
    }

    if (buttons[PauseMenu::BTN_CONTINUE]->isPressed())
    {
        endState();
    }
    if (buttons[PauseMenu::BTN_MAINMENU]->isPressed())
    {
        this->gameState->endState();   
        this->endState();
        
    }
}





void PauseMenuState::update(const float& dt)
{
    updateBackground();
    updateButtonPositions();
    updateMousePosition();
    updateGUI();
}

void PauseMenuState::renderGUI()
{
    for (auto& it : buttons)
    {
        it->render(window);
    }
}

void PauseMenuState::render(sf::RenderTarget* target)
{
    if (!target)
        target = this->window;

    if (gameState)
        gameState->renderLevelManager(target);

    target->draw(this->background);

    renderGUI();
}


void PauseMenuState::updateButtonPositions() {
    sf::Vector2f viewCenter = this->window->getView().getCenter();
    sf::Vector2f viewSize = this->window->getView().getSize();

    float x = viewCenter.x - btn_Width / 2;
    float y = viewCenter.y - viewSize.y / 4;

    buttons[PauseMenu::BTN_CONTINUE]->setPosition(x, y);
    buttons[PauseMenu::BTN_MAINMENU]->setPosition(x, y + btn_Height * 1.5);
}

void PauseMenuState::updateBackground()
{
    sf::Vector2f viewCenter = window->getView().getCenter();
    sf::Vector2f viewSize = window->getView().getSize();

    background.setPosition(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f);
}

