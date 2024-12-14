#include "Headers/Brick.h"
#include "Headers/GameEventMediator.h"

Brick::Brick() {};

Brick::Brick(sf::Vector2f position, sf::Vector2f size, std::string name, bool breakable)
	: Block(position, size, name)
{
	this->breakable = breakable;
	this->isBreak = false;

	this->animationComponent = new AnimationComponent(this->entitySprite);
	initAnimations();
	
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet[name]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
}

Brick::~Brick()
{
}

void Brick::update(const float& dt) {
	updateAnimation(dt);
	if (isBreak) {
		timeDelay += dt;

		// Update all fragments
		for (auto& fragment : fragments) {
			fragment.update(dt);
		}

		// Remove the brick after fragments have fallen
		if (timeDelay >= 3.0f) {
			eventMediator->deleteBlock(this);
		}
	}
}

void Brick::reactToCollison(int collidedSide) {
	if (collidedSide == Collide_Bottom && breakable && !isBreak) {
		eventMediator->increaseScore(50);
		this->setExist(false); // Set the brick to be destroyed (not exist anymore)
		isBreak = true;
		createBrickFragments();
	}
}

void Brick::render(sf::RenderTarget* target) {
	if (isBreak) {
		// Render fragments instead of whole brick
		for (auto& fragment : fragments) {
			target->draw(fragment.sprite);
		}
	}
	else {
		target->draw(entitySprite);
	}
	
	// Optional: render hitbox for debugging
	target->draw(hitbox);
};

void Brick::initAnimations() {
	spritesSheet = {
		{"brick_1", sf::IntRect(1, 86, 16, 16)},
		{"brick_break", sf::IntRect(1, 103, 17, 17)}
	};
}
void Brick::updateAnimation(const float& dt) {
	animationComponent->setAnimationEnemies("brick_1", spritesSheet, 0.2f);
	animationComponent->update(dt);
}

void Brick::createBrickFragments() {
	fragments.clear();

	std::vector<sf::IntRect> fragmentRects = {
		sf::IntRect(1, 86, 8, 8),
		sf::IntRect(9, 86, 8, 8),
		sf::IntRect(1, 94, 8, 8),
		sf::IntRect(9, 94, 8, 8),
		sf::IntRect(17, 86, 8, 8),
		sf::IntRect(17, 94, 8, 8)
	};

	// Create more fragments
	int fragmentCount = 12 + (rand() % 4);  // 6-9 fragments

	for (int i = 0; i < fragmentCount; ++i) {
		sf::IntRect selectedRect = fragmentRects[rand() % fragmentRects.size()];

		sf::Vector2f fragmentPos(
			hitbox.getPosition().x + (rand() % (int)(hitbox.getSize().x * 2)) - (int)hitbox.getSize().x,
			hitbox.getPosition().y + (rand() % (int)(hitbox.getSize().y * 2)) - (int)hitbox.getSize().y
		);

		BrickFragment fragment(entityTexture, selectedRect, fragmentPos);

		// Scale the fragment sprite
		float scale = (hitbox.getSize().x / 16.0f) * (0.5f + (rand() % 100) / 200.0f);
		fragment.sprite.setScale(scale, scale);

		fragment.sprite.setColor(sf::Color(255, 255, 255, 200 + rand() % 56));

		fragments.push_back(fragment);
	}
}