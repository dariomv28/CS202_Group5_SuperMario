#pragma once
#include "LevelManager.h"
class W4 :
    public LevelManager
{
private:
    sf::Texture blindFoldTexture;
    sf::Sprite blindFold;
public:
    W4(PlayerManager* player, sf::RenderWindow* window);
    virtual ~W4();

    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};
