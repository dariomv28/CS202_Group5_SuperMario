#include "Headers/Bullet.h"


Bullet::Bullet(sf::Vector2f position, sf::Vector2f size, std::string name, sf::Vector2f velocity) :
	PowerUpObject(position, size, name),
	velocity(velocity)
{
	initSpritesSheet();
}

Bullet::~Bullet()
{
}

void Bullet::initSpritesSheet()
{
	spritesSheet["bullet"] = sf::IntRect(0, 0, 16, 16);
}

void Bullet::update(const float& dt) {

}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
}