#include "Headers/Bowser.h"

Bowser::Bowser()
{

}

Bowser::Bowser(sf::Vector2f position, sf::Vector2f size, float x_min, float x_max): Bowser()
{
	initAnimations();
}

Bowser::~Bowser()
{
}

void Bowser::initAnimations() {

}

void Bowser::updateAnimation(const float& dt) {

}

void Bowser::update(const float& dt) {
	updateAnimation(dt);
	move(dt);
}

void Bowser::getDamaged() {
}

void Bowser::move(const float& dt) {
}

void Bowser::reactToPlayerCollision(int collidedSide) {
}

void Bowser::reactToBlockCollision(int collidedSide) {
}

