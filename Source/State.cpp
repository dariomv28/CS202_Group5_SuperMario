#include "Headers/State.h"

State::State(StateData* stateData)
{
	this->stateData = stateData;
	this->states = stateData->states;
	this->window = stateData->window;
	this->quit = false;

}

State::~State()
{
}

const bool& State::getQuit() const
{
	return this->quit;
}

void State::checkForQuit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
		this->quit = true;
	}
}	

void State::endState()
{
	this->quit = true;
}

void State::updateMousePosition()
{
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
}






