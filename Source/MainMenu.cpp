#include "Headers/MainMenu.h"


MainMenu::MainMenu(sf::RenderWindow* window)
	: State(window)
{

}

MainMenu::~MainMenu()
{
}

void MainMenu::update(const float& dt)
{

}

void MainMenu::render(sf::RenderTarget* target)
{
	if (!target)
		target = this->window;

}