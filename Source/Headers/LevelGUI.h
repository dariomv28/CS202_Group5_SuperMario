#pragma once
#include "GUI.h"
#include "PlayerManager.h"
#include "LevelManager.h"
#include "GameEventMediator.h"


class LevelGUI {
private:
    int health;
    int coinsCollected;
    int timeCount;
    int level;
    int score;

    sf::Text characterName;
    //sf::RectangleShape healthBar;
    //sf::RectangleShape healthBarBorder;
    sf::Font font;
    sf::Text coinsLabel;
    sf::Text scoreLabel;
    sf::Text levelCount;
    sf::Text timer;
    sf::Clock clock;
    sf::Texture heartTexture;
    sf::Sprite heartSprite;
    sf::Text livesText;


    GameEventMediator* eventMediator;
public:
    LevelGUI();
    virtual ~LevelGUI();
    void setEventMediator(GameEventMediator* eventMediator);

    //Update functions
    void updateInfo();
    void updatePosition(const sf::View& view);
    void updateTime();
    void update(const sf::View& view);
    void updateFinalScore(const sf::View& view);

    void render(sf::RenderTarget* target);
    void increaseCoins(int numCoins);
    void increaseScore(int numScore);
    void updateHealth(int playerHealth);
    int getScore() const;
    int getCoins() const;

};
