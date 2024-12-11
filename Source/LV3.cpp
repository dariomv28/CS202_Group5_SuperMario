#include "Headers/LV3.h"

LV3::LV3(PlayerManager* Player, vector<Enemy*>& Enemies, vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, sf::RenderWindow* window):
	LevelManager(window) 
{
	mapManager->convert_sketch(3, Enemies, Blocks, PowerUp, Player);
}

LV3::~LV3() {

}

