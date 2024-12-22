#include "Headers/Rocket.h"

Rocket::Rocket(sf::Vector2f position, sf::Vector2f size, std::string name, sf::Vector2f velocity)
	: PowerUpObject(position, size, name), velocity(velocity) {
	existTime = 0;
	entityTexture.loadFromFile("Source/Resources/texture/Enemies.png");
	initSpritesSheet();

	entitySprite.setTexture(entityTexture);
	if (velocity.x > 0) {
		entitySprite.setTextureRect(spritesSheet["rocket_right"]);
	}
	else {
		entitySprite.setTextureRect(spritesSheet["rocket_left"]);
	}
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	entitySprite.setPosition(position);
}

Rocket::~Rocket() {
}

void Rocket::initSpritesSheet() {
	spritesSheet["rocket_left"] = sf::IntRect(87, 63, 16, 16);
	spritesSheet["rocket_right"] = sf::IntRect(35, 63, 16, 16);
}

void Rocket::update(const float& dt) {
	existTime += dt;
	if (existTime > maxTime) {
		eventMediator->deletePowerUp(this);
		return;
	}
	this->setPosition(this->getPosition() + velocity * dt);
}

void Rocket::reactToCollison() {
	eventMediator->addPlayerHealth(-1);
	eventMediator->deletePowerUp(this);
}

void Rocket::reactToEnemyCollision(Enemy* enemy) {
	
}

void Rocket::reactToBlockCollision(Block* block) {
	eventMediator->deletePowerUp(this);
}

void Rocket::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
}