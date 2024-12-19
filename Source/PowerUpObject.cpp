#include "Headers/PowerUpObject.h"

PowerUpObject::PowerUpObject() : GameObject() {
}

PowerUpObject::PowerUpObject(sf::Vector2f position, sf::Vector2f size, std::string name)
	: GameObject(position, size)
{
	initSpritesSheet();
	entityTexture.loadFromFile("Source/Resources/texture/Items_Blocks.png");
	entitySprite.setTexture(entityTexture);
	hitbox.setSize(size);
	//hitbox.setOrigin(size.x / 2, size.y / 2);
	hitbox.setPosition(sf::Vector2f(position.x, position.y));
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(-1.f);
}

void PowerUpObject::initSpritesSheet() {
	//Coins
	spritesSheet["coin_1"] = sf::IntRect(70, 38, 10, 14);
	spritesSheet["coin_2"] = sf::IntRect(81, 38, 10, 14);
	spritesSheet["coin_3"] = sf::IntRect(92, 38, 10, 14);
	
	//Mushrooms
	spritesSheet["mushroom_1"] = sf::IntRect(2, 2, 16, 16);
	spritesSheet["mushroom_2"] = sf::IntRect(19, 2, 16, 16);
	spritesSheet["mushroom_3"] = sf::IntRect(36, 2, 16, 16);
	spritesSheet["mushroom_4"] = sf::IntRect(53, 2, 16, 16);

	//Bullet
}

PowerUpObject::~PowerUpObject() {
}

void PowerUpObject::update(const float& dt) {
}

void PowerUpObject::reactToEnemyCollision(Enemy* enemy) {
}

void PowerUpObject::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
	target->draw(hitbox);
}

