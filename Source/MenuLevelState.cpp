#include "Headers/MenuLevelState.h"
#include "Headers/GameState.h"
#include "Headers/FireBuff.h"

MenuLevelState::MenuLevelState(StateData* stateData, int world) : MainMenuState(stateData),level(0)
{
    // Reinitialize buttons with level-specific content
    this->world = world;
    this->initButtons();
	transitionAlpha = 0.0f;
}

MenuLevelState::~MenuLevelState()
{
}

void MenuLevelState::initButtons()
{
	float x = window->getSize().x / 2 - btn_Width / 2;
	float y = window->getSize().y / 2.2;

	// Init World text
	worldText.setFont(fontTitle);
	worldText.setString("WORLD " + std::to_string(world));

	// Adjust the font size and color for better visibility
	worldText.setCharacterSize(60); // Increase size for emphasis
	worldText.setFillColor(sf::Color::Yellow); // Use a bright contrasting color
	worldText.setOutlineThickness(5); // Add outline for better readability
	worldText.setOutlineColor(sf::Color::Blue); // Red outline for contrast

	// Position the text in the center of the screen
	worldText.setPosition(SCREEN_WIDTH / 2 - worldText.getGlobalBounds().width / 2,
		y - worldText.getGlobalBounds().height * 2);

	//y += btn_Height * 1.5;

	buttons.resize(nButtons);

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

void MenuLevelState::updateTransitionEffect(const float& dt) {
	if (transitioningOut) {
		transitionAlpha += dt * 255.f * 2.f;
		if (transitionAlpha >= 255.f) {
			transitioningOut = 0;
			transitionAlpha = 0.f;
			if (level == 1) {
				GameState* gameState = new GameState(this->stateData, world, 1);
				gameState->reloadLevel();
				this->states->push(gameState);
			}
			else if (level == 2) {
				GameState* gameState = new GameState(this->stateData, world, 2);
				gameState->reloadLevel();
				this->states->push(gameState);
			}

			else if (level == 3) {
				GameState* gameState = new GameState(this->stateData, world, 3);
				gameState->reloadLevel();
				this->states->push(gameState);
			}
		}
	}
};

void MenuLevelState::updateGUI()
{

    for (auto& it : buttons)
    {
        it->update(mousePosWindow);
    }

    // If user hasn't completed the previous level, disable these buttons
	// buttons[BTN_LEVEL2]->setDisable(!this->stateData->userData->getCompleted(world, 1));
	// buttons[BTN_LEVEL3]->setDisable(!this->stateData->userData->getCompleted(world, 2));
    
    // Existing mouse press handlers
    if (buttons[BTN_LEVEL1]->isPressed())
    {
		transitioningOut = true;
		level = 1; // Set level to transition to
    }
    else if (buttons[BTN_LEVEL2]->isPressed())
    {
		transitioningOut = true;
		level = 2; // Set level to transition to
    }
    else if (buttons[BTN_LEVEL3]->isPressed()) {
		transitioningOut = true;
		level = 3; // Set level to transition to
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
	updateTransitionEffect(dt);
}

void MenuLevelState::render(sf::RenderTarget* target)
{
    if (!target)
	{
		target = window;
	}
    target->draw(background[world]);
	target->draw(logo);
	target->draw(worldText);
	for (auto& it : buttons)
	{
		it->render(target);
	}

	if (transitioningOut) {
		sf::RectangleShape overlay(sf::Vector2f(window->getSize()));
		overlay.setFillColor(sf::Color(0, 0, 0, static_cast<sf::Uint8>(transitionAlpha)));
		target->draw(overlay);
	}
}
