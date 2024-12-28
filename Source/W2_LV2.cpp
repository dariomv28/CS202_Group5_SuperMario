#include "Headers/W2_LV2.h"

W2_LV2::W2_LV2(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2, 2, Enemies, Blocks, PowerUps, player);

	std::unordered_multimap<std::string, std::pair<float, float>> noBoundaries = {
		{"K", {10847, 768}},
		{"K", {10847, 768}},

		{"G", {10447, 768}},
		{"G", {10347, 768}},
	};

	for (auto x : noBoundaries) {
		if (x.first == "K") {
			Enemies.push_back(new Koopa(sf::Vector2f(x.second.first, x.second.second), sf::Vector2f(64.f, 64.f)));
		}
		else if (x.first == "G") {
			Enemies.push_back(new Goomba(sf::Vector2f(x.second.first, x.second.second), sf::Vector2f(64.f, 64.f)));
		}
	}

	std::unordered_multimap<std::string, std::pair<float, std::pair<float, std::pair<float, float>>>> boundaries = {
		{"K", {1700, {768, {1600, 2174}}} },
		
		{"G", {3400, {512, {3390, 4087}}} },
		{"K", {3500, {512, {3390, 4087}}} },

		{"K", {4600, {576, {4552, 4922}}} },

		{"G", {5800, {768, {5700, 7482}}} },
		{"G", {5900, {768, {5700, 7482}}} },
		{"K", {6200, {768, {5700, 7482}}} },
		{"K", {7000, {768, {5700, 7482}}} },

		{"K", {6200, {320, {6074, 6919}}} },
		{"G", {6500, {320, {6074, 6919}}} },
	};

	for (auto x : boundaries) {
		if (x.first == "K") {
			Enemies.push_back(new Koopa(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "G") {
			Enemies.push_back(new Goomba(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
	}

	Blocks.push_back(new MovingBlock(sf::Vector2f(2200.f, 300.f), sf::Vector2f(64.f, 64.f), "snow_ground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(2800.f, 300.f), sf::Vector2f(64.f, 64.f), "snow_ground_mid", 100.f, 300.f));

	initGameEventMediator();
}

W2_LV2::~W2_LV2() {
	
}