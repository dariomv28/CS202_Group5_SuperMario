#include "Headers/FireBuff.h"
#include "Headers/Bullet.h"

FireBuff::FireBuff() {
	type = "fire";
}

FireBuff::~FireBuff() {
}

void FireBuff::applyBuff(PlayerManager* player, GameEventMediator* eventMediator) {
	if (player->isMoveLeft()) {
		direction = -1;
	}
	else if (player->isMoveRight()) {
		direction = 1;
	}
	//Check if user pressed F
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::F)) {
		return;
	}

	if (reloadTimer.getElapsedTime().asSeconds() >= reloadTime) {
		reloadTimer.restart();
		//Spawn Bullet
		sf::Vector2f bulletSize = sf::Vector2f(32.f, 32.f);
		sf::Vector2f bulletPosition = player->getPosition();
		sf::Vector2f bulletVelocity = sf::Vector2f(direction*750.f, 0.f);
		std::string sender = "player";
		Bullet* bullet = new Bullet(bulletPosition, bulletSize, "bullet", sender, bulletVelocity);
		eventMediator->spawnPowerUp(bullet);	
	}
}
