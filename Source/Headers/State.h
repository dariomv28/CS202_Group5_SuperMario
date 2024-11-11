#pragma once
#include "stdafx.h"
#include "GUI.h"
#include "GameState.h"

class State;

class StateData
{
public:
	StateData() {
		window = nullptr;
		states = nullptr;
	}

	//Variables
	sf::RenderWindow* window;
	std::stack<State*>* states;
};

class State
{
protected:
	StateData* stateData;
	
	sf::RenderWindow* window;
	std::stack<State*>* states;
	sf::Vector2i mousePosWindow;

	bool quit;

public:
	State(StateData* stateData);
	virtual ~State();

	const bool& getQuit() const;

	virtual void checkForQuit();

	virtual void endState();
		
	virtual void updateMousePosition();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;	
};

