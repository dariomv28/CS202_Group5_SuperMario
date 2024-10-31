#pragma once
#include "State.h"

class MainMenu : 
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
	MainMenu(sf::RenderWindow* window);
	virtual ~MainMenu();

	void update(const float& dt);
	void render(sf::RenderTarget* target = nullptr);
};

