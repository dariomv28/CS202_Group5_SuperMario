#include "Headers/W3_LV2.h"

W3_LV2::W3_LV2(PlayerManager* player, sf::RenderWindow* window) :
	LevelManager(player, window)
{
	mapManager->convert_sketch(3, 2, Enemies, Blocks, PowerUps, player);
	blindFoldTexture.loadFromFile("Source/Resources/texture/BlindFold.png");
	blindFold.setTexture(blindFoldTexture);
	blindFold.setPosition(0, 0);
	blindFold.setScale(4*SCREEN_HEIGHT/blindFold.getGlobalBounds().height, 4*SCREEN_HEIGHT / blindFold.getGlobalBounds().height);

	std::unordered_multimap<std::string, std::pair<float, std::pair<float, std::pair<float, float>>>> boundaries = {
	{"K", {2200, {576, {2000, 2550}}} },

	{"G", {3300, {134, {3200, 5883}}} },
	{"K", {3400, {134, {3200, 5883}}} },
	{"G", {3600, {134, {3200, 5883}}} },
	{"K", {3800, {134, {3200, 5883}}} },

	{"G", {6300, {640, {6272, 7021}}} },
	{"K", {6600, {640, {6272, 7021}}} },

	{"G", {8500, {448, {8450, 9149}}} },
	{"K", {9000, {448, {8450, 9149}}} },

	{"G", {8300, {640, {8287, 9536}}} },
	{"K", {8500, {640, {8287, 9536}}} },
	{"G", {8700, {640, {8287, 9536}}} },
	{"K", {9100, {640, {8287, 9536}}} },

	{"K", {11200, {640, {11083, 11392}}} },
	};

	for (auto x : boundaries) {
		if (x.first == "K") {
			Enemies.push_back(new Koopa(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
		else if (x.first == "G") {
			Enemies.push_back(new Goomba(sf::Vector2f(x.second.first, x.second.second.first), sf::Vector2f(64.f, 64.f), x.second.second.second.first, x.second.second.second.second));
		}
	}

	initGameEventMediator();
}

W3_LV2::~W3_LV2() {

}

void W3_LV2::update(const float& dt) {
	LevelManager::update(dt);
	//Set the position of the blindfold so that player is always in the center
	blindFold.setPosition(player->getPosition().x - blindFold.getGlobalBounds().width/2 - CELL_SIZE, 
		player->getPosition().y - blindFold.getGlobalBounds().height / 2 + 2*CELL_SIZE);
}

void W3_LV2::render(sf::RenderTarget* target) {
    if (!target) {
        target = window;
    }
    mapManager->draw_map(target);
    player->render(target);

    //Only render the blocks that are within the view
    //Get the view bounds
    sf::Vector2f viewCenter = target->getView().getCenter();
    sf::Vector2f viewSize = target->getView().getSize();

    sf::FloatRect viewBounds(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f, viewSize.x, viewSize.y);

    for (auto& Block : Blocks) {
        if (Block->hitbox.getGlobalBounds().intersects(viewBounds)) {
            Block->render(target);
        }
    }
    for (auto& Enemy : Enemies) {
        if (Enemy->hitbox.getGlobalBounds().intersects(viewBounds))
            Enemy->render(target);
    }

    for (auto& PowerUp : PowerUps) {
        if (PowerUp->hitbox.getGlobalBounds().intersects(viewBounds)) {
            PowerUp->render(target);
        }
    }
    
    target->draw(blindFold);
    levelGUI->render(target);

    if (chatBot) {
        chatUI->render(target);
    }
}