#include "Headers/MainMenuState.h"
#include "Headers/MenuWorldState.h"
#include "Headers/MenuCharacterSelectionState.h"


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

void MainMenuState::initButtons()
{
	buttons.resize(nButtons);

	float x = window->getSize().x / 2 - btn_Width / 2;
	float y = window->getSize().y / 2.2;

	buttons[BTN_CONTINUE] = new GUI::TextureButton(false,
		x, y, btn_Width, btn_Height,
		&font, "continue", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png"
	);
	
	y += btn_Height * 1.5;
	buttons[BTN_NEWGAME] = new GUI::TextureButton(false,
		x, y, btn_Width, btn_Height,
		&font, "new game", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png"
	);

	y += btn_Height * 1.5;
	buttons[BTN_LEADER] = new GUI::TextureButton(false,
		x, y, btn_Width, btn_Height,
		&font, "leader board", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png"
	);

	y += btn_Height * 1.5;
	buttons[BTN_EXIT] = new GUI::TextureButton(false, 
		x, y, btn_Width, btn_Height,
		&font, "exit", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png", 
		"Source/Resources/texture/menu_button.png"
	);

}

MainMenuState::MainMenuState(StateData* stateData)
	: State(stateData)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initButtons();
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

    // Keyboard navigation
    //static int currentButtonIndex = 0;

    //// Move selection up
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    //{
    //    // Prevent multiple rapid changes
    //    static sf::Clock keyTimer;
    //    if (keyTimer.getElapsedTime().asMilliseconds() > 100)
    //    {
    //        currentButtonIndex = (currentButtonIndex - 1 + buttons.size()) % buttons.size();
    //        keyTimer.restart();
    //    }
    //}

    //// Move selection down
    //if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    //{
    //    // Prevent multiple rapid changes
    //    static sf::Clock keyTimer;
    //    if (keyTimer.getElapsedTime().asMilliseconds() > 100)
    //    {
    //        currentButtonIndex = (currentButtonIndex + 1) % buttons.size();
    //        keyTimer.restart();
    //    }
    //}

    //for (size_t i = 0; i < buttons.size(); ++i)
    //{
    //    if (i == currentButtonIndex)
    //    {
    //        buttons[i]->highlight(true);
    //    }
    //}

    //// Add a static flag to track key state
    //static bool enterReleased = false;

    //// Select button with Enter or Space
    //if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) ||
    //    sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) &&
    //    enterReleased)
    //{
    //    static sf::Clock keyTimer;
    //    if (keyTimer.getElapsedTime().asMilliseconds() > 150)
    //    {
    //        // Reset the enter released flag
    //        enterReleased = false;

    //        // Simulate button press for the currently selected button
    //        if (currentButtonIndex == BTN_CONTINUE)
    //        {
    //            std::cout << "Continue Pressed\n";
    //            this->stateData->audio->playbuttonSound();
    //        }
    //        else if (currentButtonIndex == BTN_NEWGAME)
    //        {
    //            this->states->push(new MenuWorldState(this->stateData));
    //            this->stateData->audio->playbuttonSound();
    //        }
    //        else if (currentButtonIndex == BTN_LEADER)
    //        {
    //            std::cout << "Leader Board Pressed\n";
    //            this->stateData->audio->playbuttonSound();
    //        }
    //        else if (currentButtonIndex == BTN_EXIT)
    //        {
    //            this->stateData->audio->playbuttonSound();
    //            endState();
    //        }
    //    }
    //}

    //// Reset the flag when the key is released
    //if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) &&
    //    !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    //{
    //    enterReleased = true;
    //}

    // Existing mouse press handlers
    if (buttons[BTN_CONTINUE]->isPressed())
    {
        std::cout << "Continue Pressed\n";

        // this->states->push(new GameState(this->stateData))
        // player->update position.x
        // update user data
    }
    if (buttons[BTN_NEWGAME]->isPressed())
    {
        this->states->push(new MenuCharacterSelectionState(this->stateData));
    }
    if (buttons[BTN_LEADER]->isPressed())
    {
        std::cout << "Leader Board Pressed\n";
    }
    if (buttons[BTN_EXIT]->isPressed())
    {
        endState();
    }
}

void MainMenuState::update(const float& dt)
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