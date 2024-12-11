#pragma
#ifndef LV1_H
#define LV1_H

#include "LevelManager.h"

class LV1 : public LevelManager {
public:
    LV1(PlayerManager* Player, vector<Enemy*>& Enemies, vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, sf::RenderWindow *window);
    ~LV1();

};

#endif // LV1_H

