#include "Headers/GameState.h"

GameState::GameState(sf::RenderWindow* window) : State(window) {

}

GameState::~GameState() {

}

void GameState::endState() {
	std::cout << "Ending GameState!" << "\n";
}

void GameState::updateKeyBinds(const float& dt) {
	this->checkForQuit();
}

void GameState::update(const float& dt) {
	// Update the state of GameState
	this->updateKeyBinds(dt);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		std::cout << "A" << "\n";
	}
}

void GameState::render(sf::RenderTarget* target) {

}
