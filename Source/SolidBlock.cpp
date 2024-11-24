#include "Headers/SolidBlock.h"

SolidBlock::SolidBlock() : Block() {
}

SolidBlock::SolidBlock(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicEngine, std::string name)
	: Block(position, size, physicEngine, name)
{
	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet[name]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);
}



SolidBlock::~SolidBlock() {
}

void SolidBlock::update(const float& dt) {

}

void SolidBlock::reactToObject(PlayerManager* player, std::vector<Block*> blocks, std::vector<Enemy> enemies) {

}

void SolidBlock::render(sf::RenderTarget* target) {
	target->draw(entitySprite);
}