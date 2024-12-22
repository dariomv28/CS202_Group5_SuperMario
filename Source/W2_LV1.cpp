#include "Headers/W2_LV1.h"

W2_LV1::W2_LV1(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(2,1, Enemies, Blocks, PowerUps, player);
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



