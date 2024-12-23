#include "Headers/FireBuff.h"
#include "Headers/Bullet.h"
#include "Headers/GameEventMediator.h"

FireBuff::FireBuff() {
	type = "fire";
}

FireBuff::~FireBuff() {
}

void FireBuff::applyBuff(GameEventMediator* eventMediator) {

	//Check if user pressed F
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		return;
	}
	//Get the curent position of the mouse
	// The position is affected by the view
	sf::RenderWindow* window = eventMediator->getWindow();
	sf::Vector2i mouseScreenPosition = sf::Mouse::getPosition(*window);
	sf::Vector2f mousePosition = (*window).mapPixelToCoords(mouseScreenPosition);

	//The direction of the bullet is from the player to the mouse

	sf::Vector2f playerPosition = eventMediator->getPlayerPosition();

	sf::Vector2f directionVector = sf::Vector2f(mousePosition.x - playerPosition.x, mousePosition.y - playerPosition.y);
	
	//Normalize the vector
	float length = sqrt(directionVector.x * directionVector.x + directionVector.y * directionVector.y);
	sf::Vector2f direction = sf::Vector2f(directionVector.x / length, directionVector.y / length);


	if (reloadTimer.getElapsedTime().asSeconds() >= reloadTime) {
		reloadTimer.restart();
		//Spawn Bullet
		sf::Vector2f bulletSize = sf::Vector2f(32.f, 32.f);
		sf::Vector2f bulletPosition = eventMediator->getPlayerPosition();
		sf::Vector2f bulletVelocity = sf::Vector2f(direction.x *750.f, direction.y * 750.f);
		std::string sender = "player";
		Bullet* bullet = new Bullet(bulletPosition, bulletSize, "bullet", sender, bulletVelocity);
		eventMediator->spawnPowerUp(bullet);	
	}
}
