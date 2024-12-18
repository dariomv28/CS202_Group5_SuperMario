#include "Headers/CloudBlock.h"

CloudBlock::CloudBlock(sf::Vector2f position, sf::Vector2f size, std::string name, float initTime)
	: Block(position, size, name)
{
	this->setExist(true);
	initSpritesSheet();
	curTime = initTime;

	entitySprite.setTexture(entityTexture);
	entitySprite.setTextureRect(spritesSheet["cloudblock"]);
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);

}

CloudBlock::~CloudBlock()
{
}

void CloudBlock::initSpritesSheet()
{
	spritesSheet["cloudblock"] = sf::IntRect(1, 215, 64, 16);
}

void CloudBlock::update(const float& dt)
{
	curTime += dt;
	if (this->getExist()) {
		if (curTime >= appearTime)
		{
			curTime = 0;
			this->setExist(false);
		}
	}
	else {
		if (curTime >= disappearTime)
		{
			curTime = 0;
			this->setExist(true);
		}
	}
}

void CloudBlock::reactToCollison(int collidedSide)
{
}

void CloudBlock::render(sf::RenderTarget* target)
{
	if (this->getExist())
	{
		target->draw(entitySprite);
	}
}


