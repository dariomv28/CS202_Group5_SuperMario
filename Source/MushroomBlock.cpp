#include "Headers/MushroomBlock.h"
#include "Headers/Mushroom.h"
#include "Headers/GameEventMediator.h"

MushroomBlock::MushroomBlock() : Block() {
}

MushroomBlock::MushroomBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int type)
	: Block(position, size, name)
{
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["coin_block_1"]);

	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
	entitySprite.setPosition(sf::Vector2f(position.x, position.y));
	this->type = type;
}

MushroomBlock::~MushroomBlock() {
}

void MushroomBlock::update(const float& dt) {

}

void MushroomBlock::reactToCollison(int collidedSide) {
	//Spawn a mushroom
	if (type == 0) return;
	if (collidedSide == Collide_Bottom) {
		//Spawn a mushroom
		eventMediator->spawnPowerUp(new Mushroom(sf::Vector2f(entitySprite.getPosition().x, entitySprite.getPosition().y - CELL_SIZE), sf::Vector2f(CELL_SIZE, CELL_SIZE), "mushroom", type));
		
		//Disable this block
		type = 0;
		entitySprite.setTextureRect(spritesSheet["empty_coin_block"]);
	}
}

void MushroomBlock::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
	target->draw(hitbox);
}