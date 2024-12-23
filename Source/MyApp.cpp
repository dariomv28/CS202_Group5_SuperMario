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
	//sf::VideoMode window_bounds(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT);
	

	unsigned framerate_limit = 120;
	bool vertical_sync_enabled = false;

	if (ifs.is_open()) {
		std::getline(ifs, title);
		ifs >> window_bounds.width >> window_bounds.height;
		//int tmpx, tmpy;
		//ifs >> tmpx >> tmpy;
		ifs >> framerate_limit;
		ifs >> vertical_sync_enabled;
	}

	this->window = new sf::RenderWindow(window_bounds, title);
	//this->window(sf::VideoMode, "Super Mario Bros", sf::Style::Close);

	this->window->setFramerateLimit(framerate_limit);
	this->window->setVerticalSyncEnabled(vertical_sync_enabled);

	//test by Minh Khoa
	//this->window = new sf::RenderWindow(sf::VideoMode(SCREEN_RESIZE * SCREEN_WIDTH, SCREEN_RESIZE * SCREEN_HEIGHT), "Super Mario Bros", sf::Style::Close);
	//window->setPosition(sf::Vector2i(window->getPosition().x, window->getPosition().y - 90));


}

void MyApp::initStateData()
{
	this->stateData.window = this->window;
	this->stateData.states = &this->states;
}

void MyApp::initStates()
{
	this->states.push(new MainMenuState(&this->stateData));
}

void MyApp::initAudioSystem() {
	audio = AudioSystem::getInstance();
}

// Constructors & Destructors	

MyApp::MyApp()
{
	this->initVariables();
	this->initWindow();
	this->initStateData();
	this->initStates();
	this->initAudioSystem();
}

MyApp::~MyApp()
{
	stateData.userData->saveData();
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

	// std::cout << "Delta time: " << this->dt << "\n";

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
	// this->updateDT();
	this->updateSFMLEvents();

	if (!this->states.empty())
	{	
		if (this->states.top()->getQuit())
		{
			// std::cout << this->states.size() << "\n";
			delete this->states.top();
			this->states.pop();
			return;
		}
		this->states.top()->update(this->dt, sfEvent);
		
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
	audio->playMusic();
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