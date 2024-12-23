#include "Headers/W2_LV3.h"

W2_LV3::W2_LV3(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2, 3, Enemies, Blocks, PowerUps, player); 

	std::unordered_multimap<std::string, std::pair<float, float>> noBoundaries = {
		{"G", {6231, 448}},
		{"K", {6231, 448}},
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
		{"G", {1100, {384, {923, 1466}}} },
		{"K", {1200, {384, {923, 1466}}} },

		{"G", {1800, {256, {1736, 2941}}} },
		{"K", {1900, {256, {1736, 2941}}} },

		{"G", {3300, {192, {3208, 4224}}} },
		{"K", {3400, {192, {3208, 4224}}} },

		{"G", {3500, {448, {3008, 4662}}} },
		{"K", {3600, {448, {3008, 4662}}} },
		{"G", {3800, {448, {3008, 4662}}} },
		{"K", {3900, {448, {3008, 4662}}} },

		{"G", {7900, {192, {7873, 10107}}} },
		{"K", {8000, {192, {7873, 10107}}} },
		{"G", {8100, {192, {7873, 10107}}} },
		{"K", {8200, {192, {7873, 10107}}} },

		{"G", {7500, {768, {6971, 10113}}} },
		{"K", {8100, {768, {6971, 10113}}} },
		{"G", {8400, {768, {6971, 10113}}} },
		{"K", {8800, {768, {6971, 10113}}} },
		{"G", {9200, {768, {6971, 10113}}} },
		{"K", {9500, {768, {6971, 10113}}} },

		{"K", {11000, {768,{10826, 11648}}}},

		{"K", {5200, {448, {5114, 5568}}}},

		{"G", {5200, {768, {5139, 5754}}} },
		{"K", {5400, {768, {5139, 5754}}} },
	};

	for (auto x : boundaries) {
		if (x.first == "K") {
			Enemies.push_back(new Koopa(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "G") {
			Enemies.push_back(new Goomba(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
	}

	Blocks.push_back(new MovingBlock(sf::Vector2f(10400.f, 300.f), sf::Vector2f(64.f, 64.f), "snow_ground_mid", 100.f, 300.f));
	initGameEventMediator();
}

W2_LV3::~W2_LV3() {

}