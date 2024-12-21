#include "Headers/MushroomBlock.h"
#include "Headers/Mushroom.h"
#include "Headers/GameEventMediator.h"

MushroomBlock::MushroomBlock() : Block() {
}

MushroomBlock::MushroomBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int type)
	: Block(position, size, name)
{
	initSpritesSheet();
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["question_block_1"]);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	entitySprite.setPosition(sf::Vector2f(position.x, position.y));
	originalBlockPosition = position;
	this->type = type;
}

MushroomBlock::~MushroomBlock() {
}

void MushroomBlock::initSpritesSheet() {
	spritesSheet["empty_question_block"] = sf::IntRect(1, 69, 16, 16);
	spritesSheet["question_block_1"] = sf::IntRect(1, 52, 16, 16);
	spritesSheet["question_block_2"] = sf::IntRect(18, 52, 16, 16);
	spritesSheet["question_block_3"] = sf::IntRect(35, 52, 16, 16);
}

void MushroomBlock::update(const float& dt) {
	updateAnimation(dt);
}

void MushroomBlock::updateAnimation(const float& dt) {
	// Update the animation
	if (type) {
		mushroomBlockAnimationTimer += dt;
		if (mushroomBlockAnimationTimer >= 0.2) {
			entitySprite.setTextureRect(spritesSheet["question_block_" + std::to_string(mushroomBlockAnimationCurrentFrame + 1)]);
			mushroomBlockAnimationCurrentFrame = (mushroomBlockAnimationCurrentFrame + 1) % 3;
			mushroomBlockAnimationTimer = 0.0f;
		}
	}

	// Update block bounce animation
	if (isBlockBouncing) {
		blockBounceTimer += dt;

		// Move up
		if (blockBounceTimer < 0.1f) {
			entitySprite.move(0, -bounceDistance);
		}
		// Move back down
		else if (blockBounceTimer < 0.2f) {
			entitySprite.move(0, +bounceDistance);
		}
		else {
			entitySprite.setPosition(originalBlockPosition);
			isBlockBouncing = false;
			blockBounceTimer = 0.0f;
		}
	}
	else {
		entitySprite.setPosition(originalBlockPosition);
	}
}

void MushroomBlock::reactToCollison(int collidedSide) {
	//Spawn a mushroom
	if (type == 0) return;
	if (collidedSide == Collide_Bottom) {
		isBlockBouncing = true;
		blockBounceTimer = 0.0f;
		//Spawn a mushroom

		Mushroom* mushroom = new Mushroom(sf::Vector2f(entitySprite.getPosition().x, entitySprite.getPosition().y - CELL_SIZE), sf::Vector2f(CELL_SIZE, CELL_SIZE), "mushroom", type);
		mushroom->setFloatSpeed(50.0f); // Set the float speed
		eventMediator->spawnPowerUp(mushroom);
		
		//Disable this block
		type = 0;
		entitySprite.setTextureRect(spritesSheet["empty_question_block"]);
	}
}

void MushroomBlock::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
}
