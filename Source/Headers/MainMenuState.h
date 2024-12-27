#pragma once
#include "State.h"

namespace MainMenu {
	enum menu_options{ BTN_CONTINUE = 0, BTN_NEWGAME, BTN_LEADER, BTN_SETTING, BTN_EXIT };

}
class MainMenuState : 
	public State
{
protected:
	int nButtons;
	float btn_Width, btn_Height, btn_CharSize;

	sf::Texture backgroundTexture[4];
	sf::Sprite background[4];

	sf::Texture logoTexture;
	sf::Sprite logo;

	sf::Font font;
	sf::Font fontTitle;

	std::vector<GUI::Button*> buttons;
	
	sf::Text titleText;

	virtual void initVariables();
	void initTitleText();
	virtual void initBackground();
	virtual void initButtons();
	void initFonts();

public:
	MainMenuState(StateData* stateData);
	virtual ~MainMenuState();

	virtual void updateGUI();
	virtual void update(const float& dt, const sf::Event& event);

	void resetGUI();

	void renderGUI();
	virtual void render(sf::RenderTarget* target);
};

