#include "Headers/LevelManager.h"
#include "Headers/GameEventMediator.h"
// The level manager is responsible for managing the level, including the player, enemies, blocks, powerups, and the GUI

LevelManager::LevelManager(PlayerManager* player, sf::RenderWindow* window) {
	this->window = window;
    this->player = player;
    if (player == nullptr) {
        std::cout << "BUGGED PLAYER\n";
    }
	firstUpdate = true;
    mapManager = new MapManager(window);
   
	levelGUI = new LevelGUI();
	eventMediator = new GameEventMediator();
	physicsEngine = new PhysicsEngine();
    audio = AudioSystem::getInstance();
    //movementComponent = new MovementComponent();
    //livingEntity = new LivingEntity();
}

LevelManager::~LevelManager() {
    delete mapManager;
    delete levelGUI;
    delete eventMediator;
    delete physicsEngine;
    delete audio;
    //delete livingEntity;
    //delete movementComponent;
}

void LevelManager::initGameEventMediator() {
    eventMediator->addPlayer(player);
    eventMediator->addEnemy(Enemies);
    eventMediator->addBlock(Blocks);
    eventMediator->addPhysicsEngine(physicsEngine);
    eventMediator->addLevelGUI(levelGUI);
    eventMediator->addPowerUp(PowerUps);
    eventMediator->addAudioSystem(audio);
    //eventMediator->addMovementComponent(movementComponent);
    //eventMediator->addLivingEntity(livingEntity);
}


void LevelManager::update(const float& dt) {
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
    eventMediator->updateEvents(cur_dt);
    eventMediator->updateLevelGUI(window->getView());


}


void LevelManager::render(sf::RenderTarget* target) {
    if (!target) {
        target = window;
    }
	mapManager->draw_map(target);
    player->render(target);

    levelGUI->render(target);

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
	//this->draw_map(false, false, view_x, *window);
}

//MapManager::MapManager() : levelManager(nullptr) {
//    // Constructor
//}

