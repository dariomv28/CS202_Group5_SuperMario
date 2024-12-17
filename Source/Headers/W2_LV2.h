#pragma once
#include "LevelManager.h"
class W2_LV2 :
    public LevelManager
{
public:
	W2_LV2(PlayerManager* player, sf::RenderWindow* window);
	virtual ~W2_LV2();
};

