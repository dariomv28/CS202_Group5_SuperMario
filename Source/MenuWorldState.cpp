#include "Headers/MenuWorldState.h"
#include "Headers/MenuLevelState.h"
#include "Headers/SettingState.h"

MenuWorldState::MenuWorldState(StateData* stateData) : MainMenuState(stateData)
{
	// Reinitialize buttons with world-specific content
	world = 0;
	this->initButtons();
}

MenuWorldState::MenuWorldState(StateData* stateData, bool Continue) : MainMenuState(stateData)
{
	// continue old world
	std::ifstream saveFile("SaveGame.txt");
	int currentWorld;
	saveFile >> currentWorld;
	world = currentWorld;
	saveFile.close();

	this->Continue = Continue;
}

MenuWorldState::~MenuWorldState()
{
}

void MenuWorldState::initButtons()
{
	buttons.resize(nButtons);

	float x = window->getSize().x / 2 - btn_Width / 2;
	float y = window->getSize().y / 2.75;

	sf::Color idleColor(50, 50, 50, 200);
	sf::Color hoverColor(70, 70, 70, 220);
	sf::Color activeColor(90, 90, 90, 240);

	sf::Color textIdleColor(255, 255, 255, 255);
	sf::Color textHoverColor(255, 255, 200, 255);
	sf::Color textActiveColor(255, 255, 255, 255);

	buttons[WorldMenu::BTN_WORLD1] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "WORLD 1", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[WorldMenu::BTN_WORLD2] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "WORLD 2", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[WorldMenu::BTN_WORLD3] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "WORLD 3", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[WorldMenu::BTN_SETTING] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "SETTING", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;
	buttons[WorldMenu::BTN_BACKTOMAIN] = new GUI::TextButton(false,
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

	if (buttons[WorldMenu::BTN_WORLD1]->isPressed())
	{
		world = 1;
		states->push(new MenuLevelState(stateData, 1));
		this->stateData->audio->playLevel1Music();

	}
	else if (buttons[WorldMenu::BTN_WORLD2]->isPressed())
	{
		world = 2;
		states->push(new MenuLevelState(stateData, 2));
		this->stateData->audio->playLevel2Music();

	}
	else if (buttons[WorldMenu::BTN_WORLD3]->isPressed())
	{
		world = 3;
		states->push(new MenuLevelState(stateData, 3));
		this->stateData->audio->playLevel3Music();

	}
	else if (buttons[WorldMenu::BTN_SETTING]->isPressed())
	{
		states->push(new SettingState(stateData, this));
	}
	else if (buttons[WorldMenu::BTN_BACKTOMAIN]->isPressed())
	{
		this->stateData->audio->playMusic();
		while (states->size() > 1)
		{
			states->pop();
		}
	}
}

void MenuWorldState::update(const float& dt, const sf::Event& event)
{
	if (Continue)
	{
		Continue = false;
		states->push(new MenuLevelState(stateData, world, 1));
		return;
	}
	updateMousePosition();
	updateGUI();
}

void MenuWorldState::render(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(background[world]);
	target->draw(logo);
	renderGUI();
}