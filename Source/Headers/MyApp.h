#pragma once
//#include "stdafx.h"
#include "MainMenu.h"

class MyApp
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	sf::Clock dtClock;
	
	float dt;

	std::stack<State*> states;

	void initVariables();
	void initStates();
	void initWindow();

public:
	//Constructors & Destructors
	MyApp();
	virtual ~MyApp();

	//Functions

	//Regular

	//Update
	void updateDT();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

