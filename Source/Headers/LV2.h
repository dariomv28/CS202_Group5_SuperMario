#pragma once
#ifndef LV2_H
#define LV2_H

#include "LevelManager.h"

class LV2 : public LevelManager {
public:
    LV2(PlayerManager* player, sf::RenderWindow* window);
    ~LV2();

};

#endif

