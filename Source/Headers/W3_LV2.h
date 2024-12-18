#pragma once
#include "LevelManager.h"
class W3_LV2 :
    public LevelManager
{
private:
    sf::Texture blindFoldTexture;
    sf::Sprite blindFold;
public:
    W3_LV2(PlayerManager* player, sf::RenderWindow* window);
    virtual ~W3_LV2();

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

