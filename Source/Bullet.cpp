#include "Headers/Bullet.h"
#include "Headers/Enemy.h"


Bullet::Bullet(sf::Vector2f position, sf::Vector2f size, std::string name, std::string sender, sf::Vector2f velocity) :
	PowerUpObject(position, size, name), sender(sender),
	velocity(velocity)
{
	animationTimer = 0.f;
	animationCurrentFrame = 1;
	initSpritesSheet();

	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["bullet_1"]);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	entitySprite.setPosition(position);
}

Bullet::~Bullet()
{
}

void Bullet::initSpritesSheet()
{
	spritesSheet["bullet_1"] = sf::IntRect(2, 70, 8, 8);
	spritesSheet["bullet_2"] = sf::IntRect(11, 70, 8, 8);
	spritesSheet["bullet_3"] = sf::IntRect(20, 70, 8, 8);
	spritesSheet["bullet_4"] = sf::IntRect(29, 70, 8, 8);
}

void Bullet::update(const float& dt) {
	updateAnimation(dt);
	//sf::Vector2f gravity = sf::Vector2f(0.f, 5000.f);
	//sf::Vector2f combinedVelocity = velocity + gravity*dt;
	this->setPosition(this->getPosition() + velocity * dt);

}

void Bullet::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
}

void Bullet::reactToCollison()
{
	if (sender == "enemy") {
		eventMediator->addPlayerHealth(-1);
		eventMediator->deletePowerUp(this);
	}
}

void Bullet::reactToEnemyCollision(Enemy* enemy)
{
	enemy->getDamaged();
	eventMediator->deletePowerUp(this);
}

void Bullet::reactToBlockCollision(Block* block)
{
	this->eventMediator->deletePowerUp(this);
}

void Bullet::updateAnimation(const float& dt)
{
	animationTimer += dt;
	if (animationTimer >= 0.1f) {
		entitySprite.setTextureRect(spritesSheet["bullet_" + std::to_string(animationCurrentFrame + 1)]);
		animationCurrentFrame = (animationCurrentFrame + 1) % 4;
		animationTimer = 0.0f;
	}
}