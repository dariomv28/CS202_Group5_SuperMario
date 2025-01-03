#include "Headers/LevelManager.h"

// The level manager is responsible for managing the level, including the player, enemies, blocks, powerups, and the GUI

LevelManager::LevelManager(PlayerManager* player, sf::RenderWindow* window) {
	this->window = window;
    this->player = player;

    finishedLevel = new bool(false);

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

void LevelManager::updateFinalScore() {
	levelGUI->updateFinalScore(window->getView());
}

int LevelManager::getScore()
{
	return levelGUI->getScore();

}

void LevelManager::initGameEventMediator() {
    eventMediator->addPlayer(player);
    eventMediator->addEnemy(Enemies);
    eventMediator->addBlock(Blocks);
    eventMediator->addPhysicsEngine(physicsEngine);
    eventMediator->addLevelGUI(levelGUI);
    eventMediator->addPowerUp(PowerUps);
    eventMediator->addAudioSystem(audio);
    eventMediator->addWindow(window);
    eventMediator->addfinishedLevel(finishedLevel);
    //eventMediator->addMovementComponent(movementComponent);
    //eventMediator->addLivingEntity(livingEntity);
}

void LevelManager::update(const float& dt) {
    //std::cout << "LevelManager::update " << *finishedLevel << std::endl;

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
        return;
    }
    if (firstUpdate)
    {
        firstUpdate = false;
        return;
    }
    if (mapManager) {
        mapManager->update(player, dt);
    }

    eventMediator->updateInput(dt);
    eventMediator->updateEvents(dt);
    eventMediator->updateLevelGUI(window->getView());
    
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
    LLMService* llmService = new OllamaService();

    // Create chat component
    chatComponent = new ChatComponent(llmService);

    chatUI = new ChatUI(chatComponent, this->window);
}