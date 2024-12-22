#include "Headers/MenuWorldState.h"
#include "Headers/MenuLevelState.h"

MenuWorldState::MenuWorldState(StateData* stateData) : MainMenuState(stateData)
{
	// Reinitialize buttons with world-specific content
	world = 0;
	this->initButtons();
}

MenuWorldState::~MenuWorldState()
{
}

void MenuWorldState::initButtons()
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

	buttons[BTN_WORLD1] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "WORLD 1", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[BTN_WORLD2] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "WORLD 2", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[BTN_WORLD3] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "WORLD 3", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[BTN_BACKTOMAIN] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "BACK", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);
}

void MenuWorldState::updateGUI()
{
	for (auto& it : buttons)
	{
		it->update(mousePosWindow);
	}

	if (buttons[BTN_WORLD1]->isPressed())
	{
		world = 1;
		states->push(new MenuLevelState(stateData, 1));
		this->stateData->audio->playLevel1Music();

	}
	else if (buttons[BTN_WORLD2]->isPressed())
	{
		world = 2;
		states->push(new MenuLevelState(stateData, 2));
		this->stateData->audio->playLevel2Music();

	}
	else if (buttons[BTN_WORLD3]->isPressed())
	{
		world = 3;
		states->push(new MenuLevelState(stateData, 3));
		this->stateData->audio->playLevel3Music();

	}
	else if (buttons[BTN_BACKTOMAIN]->isPressed())
	{
		this->stateData->audio->playMusic();
		while (states->size() > 1)
		{
			states->pop();
		}
	}
}

void MenuWorldState::update(const float& dt)
{
	updateMousePosition();
	updateGUI();
}

void MenuWorldState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(background[world]);
	renderGUI();
}