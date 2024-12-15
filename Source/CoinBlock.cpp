#include "Headers/CoinBlock.h"
#include "Headers/GameEventMediator.h"

CoinBlock::CoinBlock()
{
	this->numCoins = 0;
}

CoinBlock::CoinBlock(sf::Vector2f position, sf::Vector2f size, std::string name, int numCoins) :
	Block(position, size, name) 
{
	initSpritesSheet();
	this->numCoins = numCoins;
	entitySprite.setTexture(entityTexture);
	
	entitySprite.setTextureRect(spritesSheet["question_block_1"]); 
	entitySprite.setPosition(position);
	entitySprite.setScale(size.x / entitySprite.getGlobalBounds().width, size.y / entitySprite.getGlobalBounds().height);

	initAnimations();
}

CoinBlock::~CoinBlock()
{
}

void CoinBlock::initSpritesSheet()
{
	spritesSheet["empty_question_block"] = sf::IntRect(1, 69, 16, 16);
	spritesSheet["question_block_1"] = sf::IntRect(1, 52, 16, 16);
	spritesSheet["question_block_2"] = sf::IntRect(18, 52, 16, 16);
	spritesSheet["question_block_3"] = sf::IntRect(35, 52, 16, 16);
}

void CoinBlock::update(const float& dt) {
	// Update coin animations
	updateAnimation(dt);
}

void CoinBlock::reactToCollison(int collidedSide)
{
	if (collidedSide == Collide_Bottom) {
		if (numCoins == 0) return;

		isCoinAnimating = true;
		coinAnimationTimer = 0.0f;
		coinAnimationCurrentFrame = 0;

		initAnimations();

		this->eventMediator->increaseCoins(1);
		this->eventMediator->increaseScore(100);

		numCoins--;
		if (numCoins == 0) {
			entitySprite.setTextureRect(spritesSheet["empty_question_block"]);
		}
		eventMediator->playCoinSound();
	}
	
}

void CoinBlock::render(sf::RenderTarget* target)
{
	target->draw(entitySprite);
	if (isCoinAnimating) {
		target->draw(coinSprite);
	}
	target->draw(hitbox);
}

void CoinBlock::initAnimations()
{

	coinAnimationFrames = {
		sf::IntRect(sf::IntRect(52, 52, 16, 16)),
		sf::IntRect(sf::IntRect(69, 52, 16, 16)),
		sf::IntRect(sf::IntRect(86, 52, 16, 16)),
		sf::IntRect(sf::IntRect(52, 52, 16, 16)),
		sf::IntRect(sf::IntRect(69, 52, 16, 16)),
		sf::IntRect(sf::IntRect(86, 52, 16, 16))
	};

	coinSprite.setTexture(entityTexture);
	coinSprite.setTextureRect(coinAnimationFrames[0]);

	coinSprite.setPosition(
		entitySprite.getPosition().x + entitySprite.getGlobalBounds().width / 2 - 24,
		entitySprite.getPosition().y - 32
	);

	// Scale coin sprite to match block scaling
	coinSprite.setScale(
		entitySprite.getScale().x / 1.5,
		entitySprite.getScale().y / 1.5
	);
}

void CoinBlock::updateAnimation(const float& dt)
{
	if (isCoinAnimating) {
		coinAnimationTimer += dt;

		if (coinAnimationTimer >= 0.1f) { 
			
			coinSprite.move(0, -15.0f); 

			coinSprite.setTextureRect(coinAnimationFrames[coinAnimationCurrentFrame]);

			coinAnimationCurrentFrame = (coinAnimationCurrentFrame + 1) % coinAnimationFrames.size();
			coinAnimationTimer = 0.0f;

			if (coinAnimationCurrentFrame == coinAnimationFrames.size() - 1) {
				isCoinAnimating = false;
			}
		}
	}
}

