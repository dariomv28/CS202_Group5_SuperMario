#include "Headers/SettingState.h"


SettingState::SettingState(StateData* stateData, State* prevState)
	: State(stateData) {
	this->prevState = prevState;
	initVariables();
	initBackground();
	initFonts();
	initButtons();
}

SettingState::~SettingState() {
	for (auto it = buttons.begin(); it != buttons.end(); ++it) {
		delete* it;
	}
}

void SettingState::initVariables() {
	nButtons = 3;
	btn_Width = 400;
	btn_Height = 75;
	btn_CharSize = 20;
}

void SettingState::initBackground() {
	background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	background.setFillColor(sf::Color(0, 0, 0, 220));
}

void SettingState::initFonts() {
	if (!font.loadFromFile("Source/Resources/font/Super-Mario-Bros--3.ttf")) {
		throw("ERROR::MAINMENUSTATE::COULD NOT LOAD FONT");
	}
}

void SettingState::initButtons() {
	buttons.resize(nButtons);

	float x = window->getSize().x / 2 - btn_Width / 2;
	float y = window->getSize().y / 2.2;

	sf::Color idleColor(50, 50, 50, 200);
	sf::Color hoverColor(70, 70, 70, 220);
	sf::Color activeColor(90, 90, 90, 240);

	sf::Color textIdleColor(255, 255, 255, 255);
	sf::Color textHoverColor(255, 255, 200, 255);
	sf::Color textActiveColor(255, 255, 255, 255);


	bool allowSound = this->stateData->audio->getAllowSound();
	buttons[SettingMenu::BTN_SOUND] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, allowSound ? "SOUND  ON" : "SOUND  OFF", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;

	bool allowMusic = this->stateData->audio->getAllowMusic();
	buttons[SettingMenu::BTN_MUSIC] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, allowMusic ? "MUSIC  ON" : "MUSIC  OFF", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

	y += btn_Height * 1.5;

	buttons[SettingMenu::BTN_BACK] = new GUI::TextButton(false,
		x, y, btn_Width, btn_Height,
		&font, "BACK", btn_CharSize,
		textIdleColor, textHoverColor, textActiveColor,
		idleColor, hoverColor, activeColor,
		sf::Color(255, 255, 255, 50), sf::Color(255, 255, 255, 100)
	);

}

void SettingState::updateGUI() {
	sf::Vector2f mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));

	for (auto& it : buttons) {
		it->update(static_cast<sf::Vector2i>(mousePosView));
	}

	if (buttons[SettingMenu::BTN_SOUND]->isPressed()) {
		bool allowSound = this->stateData->audio->getAllowSound();
		this->stateData->audio->setAllowSound(allowSound ^ 1);
		buttons[SettingMenu::BTN_SOUND]->setText(allowSound ? "SOUND  OFF" : "SOUND  ON");
	}

	if (buttons[SettingMenu::BTN_MUSIC]->isPressed()) {
		bool allowMusic = this->stateData->audio->getAllowMusic();
		this->stateData->audio->setAllowMusic(allowMusic ^ 1);
		buttons[SettingMenu::BTN_MUSIC]->setText(allowMusic ? "MUSIC  OFF" : "MUSIC  ON");
	}

	if (buttons[SettingMenu::BTN_BACK]->isPressed()) {
		endState();
	}
}

void SettingState::update(const float& dt, const sf::Event& event) {
	updateBackground();
	updateButtonPositions();
	updateMousePosition();
	updateGUI();
}

void SettingState::renderGUI() {
	for (auto& it : buttons) {
		it->render(window);
	}
}

void SettingState::updateButtonPositions() {
	sf::Vector2f viewCenter = this->window->getView().getCenter();
	sf::Vector2f viewSize = this->window->getView().getSize();

	float x = viewCenter.x - btn_Width / 2;
	float y = viewCenter.y - viewSize.y / 4;

	buttons[SettingMenu::BTN_SOUND]->setPosition(x, y);
	buttons[SettingMenu::BTN_MUSIC]->setPosition(x, y + btn_Height * 1.5);
	buttons[SettingMenu::BTN_BACK]->setPosition(x, y + btn_Height * 3.0);
}

void SettingState::updateBackground() {
	sf::Vector2f viewCenter = window->getView().getCenter();
	sf::Vector2f viewSize = window->getView().getSize();

	background.setPosition(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f);
}

void SettingState::render(sf::RenderTarget* target) {
	if (!target)
		target = window;
	prevState->render(target);

	target->draw(background);
	renderGUI();
}
