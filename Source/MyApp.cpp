#include "Headers/MyApp.h"

// Initializers

void MyApp::initVariables()
{
	this->dt = 0;
	this->window = nullptr;
}

void MyApp::initWindow()
{
	// Read initial window data from WindowIni.txt file

	std::ifstream ifs("Config/WindowIni.txt");

	std::string title = "None";
	sf::VideoMode window_bounds(800, 600);

	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	this->window = new sf::RenderWindow(window_bounds, title);
	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void MyApp::initStates()
{
	this->states.push(new GameState(this->window));
}

// Constructors & Destructors	

MyApp::MyApp()
{
	this->initVariables();
	this->initWindow();
	this->initStates();
}

MyApp::~MyApp()
{
	delete this->window;

	while (!this->states.empty()) {
		delete this->states.top();
		this->states.pop();
	}
}

// Functions

void MyApp::updateDT()
{
	// Update the dt variable with the total time of each frame (update + render).

	this->dt = this->dtClock.restart().asSeconds();

	// Testing total time each frame
	/*system("cls");
	std::cout << this->dt << "\n";*/
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
	// End the window
	else {
		this->endApplication();
		this->window->close();
	}
}

void MyApp::render()
{
	this->window->clear();

	// Render items
	if (!this->states.empty()) {
		this->states.top()->render();
	}

	this->window->display();
}

void MyApp::run()
{
	while (this->window->isOpen())
	{
		this->updateDT();
		this->update();
		this->render();
	}
}

void MyApp::endApplication() {
	std::cout << "End the application!";
}