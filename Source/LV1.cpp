#include "Headers/LV1.h"
#include <iostream>

LV1::LV1(PlayerManager* Player, vector<Enemy*> &Enemies, vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, sf::RenderWindow *window):
	LevelManager(window)
{
	mapManager->convert_sketch(1, Enemies, Blocks, PowerUp, Player);
}

LV1::~LV1() {
  
}
