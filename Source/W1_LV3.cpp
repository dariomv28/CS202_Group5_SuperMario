#include "Headers/W1_LV3.h"

W1_LV3::W1_LV3(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(1, 3, Enemies, Blocks, PowerUps, player);

	Blocks.push_back(new MovingBlock(sf::Vector2f(4200.f, 200.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(4800.f, 200.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));

	Blocks.push_back(new MovingBlock(sf::Vector2f(7400.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(8000.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(8600.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(9200.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));
	Blocks.push_back(new MovingBlock(sf::Vector2f(9800.f, 400.f), sf::Vector2f(64.f, 64.f), "basic_leafground_mid", 100.f, 300.f));

	std::unordered_multimap<std::string, std::pair<float, std::pair<float, std::pair<float, float>>>> boundaries = {
		{"G", {400, {704.f, {32.f, 576.f}}}},
		

		{"G", {600, {576, {575, 1344}}}},
		
		{"K", {700, {576, {575, 1344}}}},

		{"G", {1400, {384, {1360, 2032}}}},
		{"K", {1400, {384, {1360, 2032}}}},

		{"G", {2800, {320, {2565, 3249}}}},
		{"K", {2800, {320, {2565, 3249}}}},

		{"K", {3800, {704, {3752, 4144}}}},


		{"FK", {7700, {300, {7450, 7950}}}},
		{"FK", {8400, {300, {8050, 8550}}}},
		{"FK", {8900, {300, {8650, 9150}}}},
		{"FK", {9500, {300, {9250, 9750}}}},
		


		{"fK", {4500, {576, {4300, 4700}}}},

		{"G", {6800, {768, {6784, 7281}}}},

		{"G", {10500, {768, {10442, 11328}}}},
		{"K", {10700, {768, {10442, 11328}}}},
		{"K", {10700, {768, {10442, 11328}}}},
		{"K", {10900, {768, {10442, 11328}}}},
	};

	Enemies.push_back(new Koopa(sf::Vector2f(12075, 768), sf::Vector2f(64.f, 64.f)));

	for (auto x : boundaries) {
		if (x.first == "K") {
			Enemies.push_back(new Koopa(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "G") {
			Enemies.push_back(new Goomba(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "FK") {
			Enemies.push_back(new FlyingKoopa(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}

	}

	initGameEventMediator();
}

W1_LV3::~W1_LV3() {

}