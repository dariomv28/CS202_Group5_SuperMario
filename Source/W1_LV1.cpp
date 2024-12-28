#include "Headers/W1_LV1.h"
#include "Headers/WinFlag.h"
#include <iostream>


W1_LV1::W1_LV1(PlayerManager* player, sf::RenderWindow *window):
	LevelManager(player, window)
{
	// Convert the sketch of World1 to the game
	mapManager->convert_sketch(1,1, Enemies, Blocks, PowerUps, player);

    // Add enemies to the game with specific boundaries: Goombas + Koopas

	Enemies.push_back(new Koopa(sf::Vector2f(700.0f, 768.0f), sf::Vector2f(64.f, 64.f)));

	Enemies.push_back(new Koopa(sf::Vector2f(2037.f, 768.0f), sf::Vector2f(64.f, 64.f)));

	Enemies.push_back(new Koopa(sf::Vector2f(3200.f, 768.0f), sf::Vector2f(64.f, 64.f)));
	
	Enemies.push_back(new Goomba(sf::Vector2f(4000.f, 768.0f), sf::Vector2f(64.f, 64.f), 3776.f, 4335.f));

	Enemies.push_back(new Goomba(sf::Vector2f(4600.f, 768.0f), sf::Vector2f(64.f, 64.f), 4552.f, 5421.f));
	Enemies.push_back(new Koopa(sf::Vector2f(4700.f, 768.0f), sf::Vector2f(64.f, 64.f), 4552.f, 5421.f));

	Enemies.push_back(new Goomba(sf::Vector2f(5200.f, 256.0f), sf::Vector2f(64.f, 64.f), 5142.f, 5571.f));

	Enemies.push_back(new Goomba(sf::Vector2f(6200.f, 512.0f), sf::Vector2f(64.f, 64.f), 6032.f, 6451.f));

	Enemies.push_back(new Goomba(sf::Vector2f(5800.f, 768.0f), sf::Vector2f(64.f, 64.f), 5706.f, 8512.f));
	Enemies.push_back(new Goomba(sf::Vector2f(5900.f, 768.0f), sf::Vector2f(64.f, 64.f), 5706.f, 8512.f));

	Enemies.push_back(new Koopa(sf::Vector2f(7100.f, 768.0f), sf::Vector2f(64.f, 64.f), 5706.f, 8512.f));
	Enemies.push_back(new Koopa(sf::Vector2f(7200.f, 768.0f), sf::Vector2f(64.f, 64.f), 5706.f, 8512.f));

	Enemies.push_back(new Koopa(sf::Vector2f(10691.f, 768.0f), sf::Vector2f(64.f, 64.f)));

	Enemies.push_back(new Koopa(sf::Vector2f(10800.f, 512.0f), sf::Vector2f(64.f, 64.f), 10764.f, 10940.f));

	Enemies.push_back(new Goomba(sf::Vector2f(9241.f, 768.0f), sf::Vector2f(64.f, 64.f)));

	Enemies.push_back(new Koopa(sf::Vector2f(8200.f, 256.f), sf::Vector2f(64.f, 64.f), 8184.f, 8374.0f));

	Enemies.push_back(new Koopa(sf::Vector2f(6800.f, 512.0f), sf::Vector2f(64.f, 64.f), 6787.f, 7157.f));

	Enemies.push_back(new Goomba(sf::Vector2f(7700.f, 512.0f), sf::Vector2f(64.f, 64.f), 7566.f, 7865.f));

	Enemies.push_back(new Goomba(sf::Vector2f(7600.f, 256.0f), sf::Vector2f(64.f, 64.f), 7555.f, 7878.f));

	Enemies.push_back(new Koopa(sf::Vector2f(1300.f, 256.0f), sf::Vector2f(64.f, 64.f), 1294.f, 1538.f));

	// Other enemies
		
	
    initGameEventMediator();
}

W1_LV1::~W1_LV1() {
  
}
