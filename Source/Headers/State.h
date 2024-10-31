#pragma once
#include "stdafx.h"

class State
{
protected:
	bool quit;
	sf::RenderWindow* window;
public:
	State(sf::RenderWindow* window);
	virtual ~State();

	const bool& getQuit() const;

	void endState();
	virtual void update(const float& dt) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;
};

