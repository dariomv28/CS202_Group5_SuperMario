#pragma once

#include "LevelManager.h"
#include "Goomba.h"
#include "Koopa.h"
#include "FlyingKoopa.h"
#include "PeteyPiranha.h"
#include "Heriss.h"

class W1_LV1 : public LevelManager {
public:
    W1_LV1(PlayerManager* player, sf::RenderWindow *window);
    ~W1_LV1();
};


