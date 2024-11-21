#pragma
#ifndef LV1_H
#define LV1_H

#include "LevelManager.h"

class LV1 : public LevelManager {
public:
    LV1(Mario* &Player, vector<Enemy*>& Enemies, sf::RenderWindow *window);
    ~LV1();

    void loadLevel() override;
    void update(float dt) override; 
    void render() override;
};

#endif // LV1_H

