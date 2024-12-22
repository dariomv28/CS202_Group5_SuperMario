#include "Headers/LevelManager.h"

// The level manager is responsible for managing the level, including the player, enemies, blocks, powerups, and the GUI

LevelManager::LevelManager(PlayerManager* player, sf::RenderWindow* window) {
	this->window = window;
    this->player = player;

	firstUpdate = true;
    mapManager = new MapManager(window);
   
	levelGUI = new LevelGUI();
	eventMediator = new GameEventMediator();
	physicsEngine = new PhysicsEngine();
    audio = AudioSystem::getInstance();

    initializeChatSystem();
    //movementComponent = new MovementComponent();
    //livingEntity = new LivingEntity();
}

LevelManager::~LevelManager() {
    SaveGame();
    delete mapManager;
    delete levelGUI;
    delete eventMediator;
    delete physicsEngine;
	delete chatComponent;
	delete llmService;
    delete chatUI;
    //delete livingEntity;
    //delete movementComponent;
}

void LevelManager::SaveGame()
{
	//- create a save file named "SaveGame.txt"
	std::ofstream saveFile("SaveGame.txt");
    
    
    // - Mario
    player->Save(saveFile);

    // -Map
	mapManager->Save(saveFile);

    saveFile.close();

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
        eventMediator->updateEvents(cur_dt);
        eventMediator->updateLevelGUI(window->getView());
    }
}


void LevelManager::render(sf::RenderTarget* target) {
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
	//this->draw_map(false, false, view_x, *window);

	if (chatBot) {
		chatUI->render(target);
	}
    levelGUI->render(target);

}

void LevelManager::initializeChatSystem() {
    // Create LLM service
//<<<<<<< HEAD
//	LLMService* llmService = new OllamaLLMService();
//=======
    LLMService* llmService = new OllamaService();
//>>>>>>> 896ddaff63316a2ac62201991f6a83440c3452ce

    // Create chat component
    chatComponent = new ChatComponent(llmService);

    chatUI = new ChatUI(chatComponent, this->window);
}