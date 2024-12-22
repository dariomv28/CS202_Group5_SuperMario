#include "Headers/Cannon.h"
#include "Headers/Rocket.h"
Cannon::Cannon() : Block() {
}

Cannon::Cannon(sf::Vector2f position, sf::Vector2f size, std::string name)
	: Block(position, size, name)
{
	reloadTimer = 0;
	initSpritesSheet();
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["cannon"]);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	entitySprite.setPosition(position);
}

Cannon::~Cannon() {
}

void Cannon::initSpritesSheet() {
	spritesSheet = {
		{"cannon", sf::IntRect(69, 137, 16, 16)}
	};
}

void Cannon::update(const float& dt) {
	if (reloadTimer < reloadDuration) {
		reloadTimer += dt;
	}
	else {
		reloadTimer = 0;
		// Spawn 2 rockets at 2 sides of the cannon
		eventMediator->spawnPowerUp(new Rocket(sf::Vector2f(this->getPosition().x - CELL_SIZE, this->getPosition().y), sf::Vector2f(CELL_SIZE-2, CELL_SIZE-2), 
			"rocket_left", sf::Vector2f(-500, 0)));
		eventMediator->spawnPowerUp(new Rocket(sf::Vector2f(this->getPosition().x + CELL_SIZE, this->getPosition().y), sf::Vector2f(CELL_SIZE-2, CELL_SIZE-2),
			"rocket_right", sf::Vector2f(500, 0)));
	}
}

void Cannon::reactToCollison(int collidedSide) {
}

void Cannon::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
}

