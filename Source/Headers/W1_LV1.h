#pragma once

#include "LevelManager.h"
#include "Goomba.h"
#include "Koopa.h"

class W1_LV1 : public LevelManager {
public:
    W1_LV1(PlayerManager* player, sf::RenderWindow *window);
    ~W1_LV1();
};


