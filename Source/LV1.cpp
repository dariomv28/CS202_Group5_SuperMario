#include "Headers/LV1.h"

#include <iostream>


LV1::LV1(PlayerManager* player, sf::RenderWindow *window):
	LevelManager(player, window)
{
	// Convert the sketch of World1 to the game
	mapManager->convert_sketch(1, Enemies, Blocks, PowerUps, player);

    // Add enemies to the game with specific boundaries

    Enemies.push_back(new Koopa(sf::Vector2f(300.f, 500.f), sf::Vector2f(64.f, 64.f)));
    Enemies.push_back(new Goomba(sf::Vector2f(700.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Koopa(sf::Vector2f(2096.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Goomba(sf::Vector2f(2777.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Koopa(sf::Vector2f(3279.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Goomba(sf::Vector2f(9327.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Koopa(sf::Vector2f(10269.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Goomba(sf::Vector2f(10960.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Koopa(sf::Vector2f(12370.f, 500.f), sf::Vector2f(64.f, 64.f)));

    Enemies.push_back(new Goomba(sf::Vector2f(13098.f, 500.f), sf::Vector2f(64.f, 64.f)));

    // Customized boundaries
    Enemies.push_back(new Goomba(sf::Vector2f(4700.f, 500.f), sf::Vector2f(64.f, 64.f), 4528.f, 5432.f));

    Enemies.push_back(new Goomba(sf::Vector2f(5200.f, 195.f), sf::Vector2f(64.f, 64.f), 5100.f, 5600.f));

    Enemies.push_back(new Goomba(sf::Vector2f(5945.f, 195.f), sf::Vector2f(64.f, 64.f), 5800.f, 6050.f));

    Enemies.push_back(new Koopa(sf::Vector2f(5800.f, 500.f), sf::Vector2f(64.f, 64.f), 5739.f, 8511.f));
    Enemies.push_back(new Koopa(sf::Vector2f(7000.f, 500.f), sf::Vector2f(64.f, 64.f), 5739.f, 8511.f));

    Enemies.push_back(new Goomba(sf::Vector2f(8348.f, 195.f), sf::Vector2f(64.f, 64.f), 8180.f, 8408.f));

    Enemies.push_back(new Goomba(sf::Vector2f(10900.f, 450.f), sf::Vector2f(64.f, 64.f), 10718.f, 10978.f));

    initGameEventMediator();
}

LV1::~LV1() {
  
}
