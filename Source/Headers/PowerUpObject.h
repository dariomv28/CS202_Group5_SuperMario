#pragma once
#include "GameObject.h"
#include "GameEventMediator.h"
class PowerUpObject :
    public GameObject
{
protected:
	std::string name;
	std::unordered_map<std::string, sf::IntRect> spritesSheet;
public:
	PowerUpObject();
	PowerUpObject(sf::Vector2f position, sf::Vector2f size, std::string name);
	void initSpritesSheet();
	virtual ~PowerUpObject();
	void update(const float& dt) override;
	virtual void reactToCollison() = 0;
	virtual void reactToEnemyCollision(Enemy* enemy);
	virtual void reactToBlockCollision(Block* block);
	void render(sf::RenderTarget* target) override;
};

