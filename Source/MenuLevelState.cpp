#include "Headers/MenuLevelState.h"
#include "Headers/GameState.h"
#include "Headers/FireBuff.h"

MenuLevelState::MenuLevelState(StateData* stateData, int world) : MainMenuState(stateData),level(0)
{
    // Reinitialize buttons with level-specific content
    this->world = world;
    this->initButtons();
}

MenuLevelState::~MenuLevelState()
{
}

void MenuLevelState::initButtons()
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

	buttons[BTN_LEVEL1] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "LEVEL 1", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[BTN_LEVEL2] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "LEVEL 2", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[BTN_LEVEL3] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "LEVEL 3", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[BTN_BACK] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "BACK", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);
}

void MenuLevelState::updateGUI()
{
    for (auto& it : buttons)
    {
        it->update(mousePosWindow);
    }
    //If user hasn't completed the previous level, disable these buttons
  //  buttons[BTN_LEVEL2]->setDisable(!this->stateData->userData->getCompleted(world, 1));
   // buttons[BTN_LEVEL3]->setDisable(!this->stateData->userData->getCompleted(world, 2));
    

    // Existing mouse press handlers
    if (buttons[BTN_LEVEL1]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData, world, 1);
        gameState->reloadLevel();
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL2]->isPressed())
    {
        GameState* gameState = new GameState(this->stateData, world, 2);
        gameState->reloadLevel();
        this->states->push(gameState);
    }
    else if (buttons[BTN_LEVEL3]->isPressed()) {
        GameState* gameState = new GameState(this->stateData, world, 3);
        gameState->reloadLevel();
        this->states->push(gameState);
    }
    else if (buttons[BTN_BACK]->isPressed())
    {
        endState();
    }
}

void MenuLevelState::update(const float& dt)
{
    //Defaut view
    window->setView(window->getDefaultView());
    updateMousePosition();
    updateGUI();
}

void MenuLevelState::render(sf::RenderTarget* target)
{
    if (!target)
	{
		target = window;
	}
    target->draw(background[world]);
	target->draw(worldText);
	for (auto& it : buttons)
	{
		it->render(target);
	}
}
