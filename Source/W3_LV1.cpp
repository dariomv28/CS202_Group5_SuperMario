#include "Headers/W3_LV1.h"

W3_LV1::W3_LV1(PlayerManager* player, sf::RenderWindow* window):
	LevelManager(player, window) 
{
	mapManager->convert_sketch(3,1, Enemies, Blocks, PowerUps, player);

	std::unordered_multimap<std::string, std::pair<float, std::pair<float, std::pair<float, float>>>> boundaries = {
		{"G", {2100, {576, {2013, 2545}}} },
		{"H", {300, {500, {100, 550}}} },
		

		{"G", {9200, {134, {9197, 9855}}} },
		{"K", {9400, {134, {9197, 9855}}} },
		{"H", {9600, {134, {9197, 9855}}} },

		{"K", {11200, {582, {11095, 11392}}} },
		{"H", {11250, {582, {11095, 11392}}} },

		{"K", {3300, {576, {3218, 3400}}} },

		{"H", {5700, {640, {5500, 5900}}} },
		
		
	};

	for (auto x : boundaries) {
		if (x.first == "K") {
			Enemies.push_back(new Koopa(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "G") {
			Enemies.push_back(new Goomba(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "H") {
			Enemies.push_back(new Heriss(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
	}

	initGameEventMediator();
}

W3_LV1::~W3_LV1() {

}

