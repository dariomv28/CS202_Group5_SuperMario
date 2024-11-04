#include "Headers/MainMenuState.h"


MainMenuState::MainMenuState(sf::RenderWindow* window)
	: State(window)
{

}

MainMenuState::~MainMenuState()
{
}

void MainMenuState::update(const float& dt)
{

}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

}