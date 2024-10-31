#include "Headers/MyApp.h"

//Initializers

void MyApp::initVariables()
{
	this->dt = 0;
	this->window = nullptr;
}

void MyApp::initWindow()
{
	//Later, should read from file Config/window.ini
	this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Mario Game");
}

void MyApp::initStates()
{
	this->states.push(new MainMenu(this->window));
}

//Constructors & Destructors	

MyApp::MyApp()
{
	this->initVariables();
	this->initWindow();
	this->initStates();
}

MyApp::~MyApp()
{
	delete this->window;
}

//Update

void MyApp::updateDT()
{
	this->dt = this->dtClock.restart().asSeconds();
}

void MyApp::updateSFMLEvents()
{
	while (this->window->pollEvent(this->sfEvent))
	{
		if (this->sfEvent.type == sf::Event::Closed)
			this->window->close();
	}
}

void MyApp::update()
{
	this->updateDT();
	this->updateSFMLEvents();

	if (!this->states.empty())
	{
		this->states.top()->update(this->dt);
		if (this->states.top()->getQuit())
		{
			this->states.top()->endState();
			delete this->states.top();
			this->states.pop();
		}
	}
}

//Render

void MyApp::render()
{
	this->window->clear();
	this->window->display();
}

//Core

void MyApp::run()
{
	while (this->window->isOpen())
	{
		this->update();
		this->render();
	}
}