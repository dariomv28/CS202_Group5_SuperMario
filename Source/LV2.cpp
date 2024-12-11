#include "Headers/LV2.h"

LV2::LV2(PlayerManager* Player, vector<Enemy*>& Enemies, vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, sf::RenderWindow* window) :
	LevelManager(window)
{
	mapManager->convert_sketch(2, Enemies, Blocks, PowerUp, Player);
}


LV2::~LV2() {

}




