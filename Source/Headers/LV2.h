#pragma once
#ifndef LV2_H
#define LV2_H

#include "LevelManager.h"

class LV2 : public LevelManager {
public:
    LV2();
    ~LV2();

    void loadLevel() override;  
    void update(float dt) override;
    void render() override;
};

#endif

