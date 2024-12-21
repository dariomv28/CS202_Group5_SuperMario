#pragma once
#include "State.h"

enum menu_options { BTN_CONTINUE = 0, BTN_NEWGAME, BTN_LEADER, BTN_EXIT };

class MainMenuState : 
	public State
{
protected:
	int nButtons;
	float btn_Width, btn_Height, btn_CharSize;

	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture logoTexture;
	sf::Sprite logo;

	sf::Font font;

	std::vector<GUI::Button*> buttons;

	void initVariables();
	void initBackground();
	virtual void initButtons();
	void initFonts();

public:
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	virtual void updateGUI();
	virtual void update(const float& dt);

	void resetGUI();

	void renderGUI();
	virtual void render(sf::RenderTarget* target);
};

