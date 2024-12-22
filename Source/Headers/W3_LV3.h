#pragma once
#include "LevelManager.h"
class W3_LV3 :
    public LevelManager
{
public:
    W3_LV3(PlayerManager* player, sf::RenderWindow* window);
    virtual ~W3_LV3();

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

