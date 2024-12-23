#include "Headers/W2_LV1.h"

W2_LV1::W2_LV1(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2,1, Enemies, Blocks, PowerUps, player);

	std::unordered_multimap<std::string, std::pair<float, float>> noBoundaries = {
		{"K", {6138, 768}},
        {"K", {6238, 768}},
        {"K", {6338, 768}},

		{"G", {6738, 768}},
        {"G", {6838, 768}},
        {"G", {6938, 768}},
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
        {"K", {580, {448, {572, 1088}}} },
        {"G", {590, {448, {572, 1088}}} },
        {"K", {580, {192, {572, 1088}}} },
        {"G", {590, {192, {572, 1088}}} },

        {"K", {1800, {768, {1664, 2156}}} },

        {"K", {6100, {320, {6088, 6929}}} },
        {"K", {6200, {320, {6088, 6929}}} },
        {"G", {6300, {320, {6088, 6929}}} },

        {"G", {9000, {768, {8588, 10368}}} },
        {"G", {9100, {768, {8588, 10368}}} },
        {"G", {9200, {768, {8588, 10368}}} },

        {"K", {9300, {768, {8588, 10368}}} },
        {"K", {9400, {768, {8588, 10368}}} },
        {"K", {9500, {768, {8588, 10368}}} },

        {"G", {9800, {320, {9600, 10432}}} },
        {"G", {10000, {320, {9600, 10432}}} },
        {"K", {10100, {320, {9600, 10432}}} },

        {"G", {10500, {384, {10496, 10689}}} },

        {"K", {11300, {768, {11206, 11648}}} },
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

	Blocks.push_back(new MovingBlock(sf::Vector2f(3974.f, 200.f), sf::Vector2f(64.f, 64.f), "snow_ground_mid", 100.f, 300.f));

	initGameEventMediator();
}


W2_LV1::~W2_LV1() {

}

void W2_LV1::update(const float& dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Tab)) {
        static sf::Clock keyTimer;
        if (keyTimer.getElapsedTime().asMilliseconds() > 300)
        {
            keyTimer.restart();
            chatBot = !chatBot;
        }
    }

    if (chatBot) {
        chatUI->update(window->getView());
    }
    else {
        float cur_dt = dt;
        if (firstUpdate)
        {
            cur_dt = 0;
            firstUpdate = false;
        }
        if (mapManager) {
            mapManager->update(player, cur_dt);
        }

        eventMediator->updateInput(cur_dt);
        //Swap move left and move right
        if (player->isMoveLeft()) {
			player->setMoveLeft(false);
			player->setMoveRight(true);
            player->isMovingLeft = false;
		}
        else if (player->isMoveRight()) {
            player->setMoveRight(false);
            player->setMoveLeft(true);
            player->isMovingLeft = true;
        }
        eventMediator->updateEvents(cur_dt);
        eventMediator->updateLevelGUI(window->getView());
    }
}



