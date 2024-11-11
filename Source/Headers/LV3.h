#pragma once
#ifndef LV3_H
#define LV3_H

#include "LevelManager.h"

class LV3 : public LevelManager {
public:
    LV3();
    ~LV3();

    void loadLevel() override;
    void update(float dt) override; 
    void render() override;  
};

#endif

