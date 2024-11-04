#pragma once
#include "State.h"

class MainMenuState : 
	public State
{
private:
	sf::RenderWindow* window;
	
	sf::Texture backgroundTexture;
	sf::Sprite background;

	sf::Texture logoTexture;
	sf::Sprite logo;

	sf::Font font;

	//void initVariables();
	//void initBackground();
	//void initFonts();
	//void initKeybinds();
	//void initText();
public:
	MainMenuState(sf::RenderWindow* window);
	virtual ~MainMenuState();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

