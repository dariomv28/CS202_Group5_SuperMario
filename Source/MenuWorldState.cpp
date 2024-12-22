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
	buttons.resize(4); // 3 worlds

	float x = window->getSize().x / 2 - btn_Width / 2;
	float y = window->getSize().y / 2.2;

	buttons[BTN_WORLD1] = new GUI::TextureButton(false,
		x, y, btn_Width, btn_Height,
		&font, "World 1", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png"
	);

	y += btn_Height * 1.5;
	buttons[BTN_WORLD2] = new GUI::TextureButton(false,
		x, y, btn_Width, btn_Height,
		&font, "World 2", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png"
	);

	y += btn_Height * 1.5;
	buttons[BTN_WORLD3] = new GUI::TextureButton(false,
		x, y, btn_Width, btn_Height,
		&font, "World 3", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png"
	);
	y += btn_Height * 1.5;
	buttons[BTN_BACKTOMAIN] = new GUI::TextureButton(false,
		x, y, btn_Width, btn_Height,
		&font, "Back", btn_CharSize,
		sf::Color::Black, sf::Color::White, sf::Color::White,
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png",
		"Source/Resources/texture/menu_button.png"
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