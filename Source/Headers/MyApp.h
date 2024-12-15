#pragma once
//#include "stdafx.h"
#include "MainMenuState.h"
#include "GameState.h"


class MyApp
{
private:
	sf::RenderWindow* window;
	sf::Event sfEvent;
	//AudioSystem* audio;
	sf::Clock dtClock;
	float dt; 

	StateData stateData;
	std::stack<State*> states; // Applying polymorphism and abstraction here!

	void initVariables();
	void initWindow();
	void initStateData();
	void initStates();
	//void initAudioSystem();

public:
	//Constructors & Destructors
	MyApp();
	virtual ~MyApp();

	//Functions

	//Regular
	void endApplication();

	//Update
	void updateDT();
	void updateSFMLEvents();
	void update();

	//Render
	void render();

	//Core
	void run();
};

