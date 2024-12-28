#pragma once
#include "LevelManager.h"
#include "Mushroom.h"
class W3_LV3 :
    public LevelManager
{
private:
    const float reloadMushroom = 5.0f;
	float reloadMushroomTimer;
	Mushroom* current_mushroom;

    sf::Texture blindFoldTexture;
    sf::Sprite blindFold;
public:
    W3_LV3(PlayerManager* player, sf::RenderWindow* window);
    virtual ~W3_LV3();

	void updateMushroom(const float& dt);
    void update(const float& dt);
    void render(sf::RenderTarget* target = nullptr);
};

