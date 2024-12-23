#include "Headers/W1_LV2.h"

W1_LV2::W1_LV2(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(1, 2, Enemies, Blocks, PowerUps, player);

	std::unordered_multimap<std::string, std::pair<float, float>> noBoundaries = {
		{"K", {769, 768}},
		{"G", {12015, 768}},
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
		{"K", {1100, {320, {1053, 1487}}}},

		{"G", {5500, {576, {5459, 5888}}}},

		{"G", {6200, {384, {5914, 6581}}}},
		{"K", {6400, {384, {5914, 6581}}}},

		{"K", {6100, {128, {6016, 6468}}}},

		{"G", {6700, {512, {6592, 7085}}}},

		{"K", {7800, {768, {7636, 8064}}}},

		{"G", {8500, {512, {8441, 9040}}}},
		{"K", {8600, {512, {8441, 9040}}}},

		{"K", {10800, {512, {10557, 10757}}}},
	};

	// Enemies.push_back(new Koopa(sf::Vector2f(6200, 384), sf::Vector2f(64.f, 64.f), 5914, 6581));

	for (auto x : boundaries) {
		if (x.first == "K") {
			Enemies.push_back(new Koopa(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "G") {
			Enemies.push_back(new Goomba(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
	}

	Blocks.push_back(new MovingBlock(sf::Vector2f(4500.f, 200.f), sf::Vector2f(64.f, 64.f), "basic_ground_mid", 100, 300));
	
	initGameEventMediator();

}

W1_LV2::~W1_LV2() {

}	