#include "Headers/W3_LV3.h"
#include "Headers/Bowser.h"
//#include "Headers/Mushroom.h"

W3_LV3::W3_LV3(PlayerManager* player, sf::RenderWindow* window):
	LevelManager(player, window) 
{
	mapManager->convert_sketch(3,3, Enemies, Blocks, PowerUps, player);
	Enemies.push_back(new Bowser(sf::Vector2f(500.f, 250.f), sf::Vector2f(128.f, 140.f), 374.f, 1120.f));
	
	// blindfold
	blindFoldTexture.loadFromFile("Source/Resources/texture/BlindFold.png");
	blindFold.setTexture(blindFoldTexture);
	blindFold.setPosition(0, 0);
	blindFold.setScale(4 * SCREEN_HEIGHT / blindFold.getGlobalBounds().height, 4 * SCREEN_HEIGHT / blindFold.getGlobalBounds().height);

	initGameEventMediator();
}

W3_LV3::~W3_LV3() {

}


void W3_LV3::updateMushroom(const float& dt) {
	reloadMushroomTimer += dt;
	if (reloadMushroomTimer >= reloadMushroom) {
		reloadMushroomTimer = 0;
		eventMediator->deletePowerUp(current_mushroom);
		current_mushroom = new Mushroom(sf::Vector2f(random(374, 1120), 768.f), sf::Vector2f(64, 64), "mushroom", 2);
		eventMediator->spawnPowerUp(current_mushroom);
	}
}
void W3_LV3::update(const float& dt) {
	updateMushroom(dt);
	LevelManager::update(dt);
	blindFold.setPosition(player->getPosition().x - blindFold.getGlobalBounds().width / 2 - CELL_SIZE,
	player->getPosition().y - blindFold.getGlobalBounds().height / 2 + 2 * CELL_SIZE);
}

void W3_LV3::render(sf::RenderTarget* target) {
	LevelManager::render(target);
}

