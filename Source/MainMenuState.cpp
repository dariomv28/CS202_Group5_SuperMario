#include "Headers/MainMenuState.h"
#include "Headers/MenuWorldState.h"
#include "Headers/MenuCharacterSelectionState.h"
#include "Headers/GameState.h"
#include "Headers/EnterNameState.h"
#include "Headers/LeaderboardState.h"

void MainMenuState::initVariables()
{
    nButtons = 4;
    btn_Width = 400;
    btn_Height = 75; 
    btn_CharSize = 20;     
}

void MainMenuState::initBackground()
{
	backgroundTexture[0].loadFromFile("Source/Resources/texture/basic_mainmenu.png");
	background[0].setTexture(backgroundTexture[0]);
	background[0].setScale(window->getSize().x / background[0].getGlobalBounds().width,
		window->getSize().y / background[0].getGlobalBounds().height);

    backgroundTexture[1].loadFromFile("Source/Resources/texture/night_mainmenu.png");
    background[1].setTexture(backgroundTexture[1]);
    background[1].setScale(window->getSize().x / background[1].getGlobalBounds().width,
        window->getSize().y / background[1].getGlobalBounds().height);


    backgroundTexture[2].loadFromFile("Source/Resources/texture/snow_mainmenu.png");
    background[2].setTexture(backgroundTexture[2]);
    background[2].setScale(window->getSize().x / background[2].getGlobalBounds().width,
		window->getSize().y / background[2].getGlobalBounds().height);

    backgroundTexture[3].loadFromFile("Source/Resources/texture/fire_mainmenu.png");
	background[3].setTexture(backgroundTexture[3]);
	background[3].setScale(window->getSize().x / background[3].getGlobalBounds().width,
        window->getSize().y / background[3].getGlobalBounds().height);

    logoTexture.loadFromFile("Source/Resources/texture/logo.png");
    logo.setTexture(logoTexture);
    logo.setScale(0.5, 0.5);
    logo.setPosition(window->getSize().x / 2 - logo.getGlobalBounds().width / 2, 50);

}

void MainMenuState::initFonts()
{
	if (!font.loadFromFile("Source/Resources/font/Super-Mario-Bros--3.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void MainMenuState::initTitleText()
{
    // Load a retro pixel-style font
    if (!fontTitle.loadFromFile("Source/Resources/font/American Captain.ttf"))
    {
        throw("ERROR::MAINMENUSTATE::FAILED_TO_LOAD_FONT");
    }

    // Set up the title text
    titleText.setFont(fontTitle);
    titleText.setString("     Group 5 - 23TT2\nSUPER MARIO GAME");
    titleText.setCharacterSize(50);

    // Style the text
    titleText.setFillColor(sf::Color(255, 255, 0)); // Bright yellow
    titleText.setOutlineThickness(3);
    titleText.setOutlineColor(sf::Color(0, 0, 0));  // Black outline

    // Center the title on the screen
    sf::Vector2u windowSize = window->getSize();
    sf::FloatRect textBounds = titleText.getLocalBounds();
    titleText.setPosition(
        windowSize.x / 2.f - textBounds.width / 2.f,
        windowSize.y / 6.f - textBounds.height / 2.f
    );
}

void MainMenuState::initButtons()
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

    buttons[BTN_CONTINUE] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "CONTINUE", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)  
    );

    y += btn_Height * 1.5;
    buttons[BTN_NEWGAME] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "NEW GAME", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
    );

    y += btn_Height * 1.5;
    buttons[BTN_LEADER] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "LEADER BOARD", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
    );

    y += btn_Height * 1.5;
    buttons[BTN_EXIT] = new GUI::TextButton(false,
        x, y, btn_Width, btn_Height,
        &font, "EXIT", btn_CharSize,
        textIdleColor, textHoverColor, textActiveColor,
        idleColor, hoverColor, activeColor,
        sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
    );
}

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
    this->initTitleText();
}

MainMenuState::~MainMenuState()
{
	for (auto it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete* it;
	}
}

void MainMenuState::updateGUI()
{
    for (auto& it : buttons)
    {
        it->update(mousePosWindow);
    }

    // Existing mouse press handlers
    if (buttons[BTN_CONTINUE]->isPressed())
    {
        this->stateData->userData->loadData();

        this->states->push(new MenuWorldState(this->stateData));

    }
    if (buttons[BTN_NEWGAME]->isPressed())
    {
        this->states->push(new EnterNameState(this->stateData));
        //this->states->push(new MenuCharacterSelectionState(this->stateData));
    }
    if (buttons[BTN_LEADER]->isPressed())
    {
        this->states->push(new LeaderboardState(this->stateData));
    }
    if (buttons[BTN_EXIT]->isPressed())
    {
        endState();
    }
}

void MainMenuState::update(const float& dt, const sf::Event& event)
{
	updateMousePosition();
	updateGUI();
}

void MainMenuState::resetGUI()
{

}

void MainMenuState::renderGUI()
{
	for (auto& it : buttons)
	{
		it->render(window);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

	target->draw(this->background[0]);
    target->draw(this->logo);
	renderGUI();
}