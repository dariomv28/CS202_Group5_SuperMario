#pragma once
#ifndef LV3_H
#define LV3_H

#include "LevelManager.h"

class LV3 : public LevelManager {
public:
	LV3(PlayerManager* Player, vector<Enemy*>& Enemies, vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, sf::RenderWindow* window);
	~LV3();

	
};

#endif

