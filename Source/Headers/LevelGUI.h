#pragma once
#include "GUI.h"
#include "PlayerManager.h"
#include "LevelManager.h"



class LevelGUI {
private:
    int health;
    int coinsCollected;
    int timeCount;
    int level;

    sf::Text healthLabel;
    sf::RectangleShape healthBar;
    sf::Font font;
    sf::Text coinsLabel;
    sf::Text levelCount;
    sf::Text timer;
    sf::Clock clock;

public:
    LevelGUI();
    virtual ~LevelGUI();

    void updateInfo(int playerHealth, int coins, int currentLevel);
    void render(sf::RenderTarget* target);
    void updatePosition(const sf::View& view);
    void updateTime();
};
