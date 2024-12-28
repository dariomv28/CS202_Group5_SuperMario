#include "Headers/PauseMenuState.h"
#include "Headers/MainMenuState.h"
#include "Headers/GUI.h"
#include "Headers/GameState.h"
#include "Headers/SettingState.h"

void PauseMenuState::initVariables()
{
    nButtons = 4;
    btn_Width = 400;
    btn_Height = 75;
    btn_CharSize = 20;
}

void PauseMenuState::initBackground()
{
    background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
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
    
    sf::Color idleColor(50, 50, 50, 200);
    sf::Color hoverColor(70, 70, 70, 220);
    sf::Color activeColor(90, 90, 90, 240);

    sf::Color textIdleColor(255, 255, 255, 255);
    sf::Color textHoverColor(255, 255, 200, 255);
    sf::Color textActiveColor(255, 255, 255, 255);

    buttons[PauseMenu::BTN_CONTINUE] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "CONTINUE", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
    );

    y += btn_Height * 1.5;
    buttons[PauseMenu::BTN_SAVEGAME] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "RETRY", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
    );
    
    y += btn_Height * 1.5;
    buttons[PauseMenu::BTN_SETTING] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "SETTING", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
    );



    y += btn_Height * 1.5;
    buttons[PauseMenu::BTN_MAINMENU] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "LEVEL MENU", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
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
    } else if (buttons[PauseMenu::BTN_SAVEGAME]->isPressed())
	{
		this->gameState->reloadLevel();
		this->endState();
	}
	else if (buttons[PauseMenu::BTN_SETTING]->isPressed())
	{
		this->states->push(new SettingState(stateData, gameState));
	}
	else
    if (buttons[PauseMenu::BTN_MAINMENU]->isPressed())
    {
        this->gameState->endState();
       // this->stateData->userData->resetPlayer(gameState->getWorld());
        this->endState();
    }
}

void PauseMenuState::update(const float& dt, const sf::Event& event)
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
        gameState->render(target);

    target->draw(this->background);

    renderGUI();
}


void PauseMenuState::updateButtonPositions() {
    sf::Vector2f viewCenter = this->window->getView().getCenter();
    sf::Vector2f viewSize = this->window->getView().getSize();

    float x = viewCenter.x - btn_Width / 2;
    float y = viewCenter.y - viewSize.y / 4;

    buttons[PauseMenu::BTN_CONTINUE]->setPosition(x, y);
	buttons[PauseMenu::BTN_SAVEGAME]->setPosition(x, y + btn_Height * 1.5);
    buttons[PauseMenu::BTN_SETTING]->setPosition(x, y + btn_Height * 3.0);
    buttons[PauseMenu::BTN_MAINMENU]->setPosition(x, y + btn_Height * 4.5);
}

void PauseMenuState::updateBackground()
{
    sf::Vector2f viewCenter = window->getView().getCenter();
    sf::Vector2f viewSize = window->getView().getSize();

    background.setPosition(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f);
}

