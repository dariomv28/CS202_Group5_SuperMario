#include "Headers/GameState.h"

using namespace std;

GameState::GameState(StateData* stateData) : State(stateData), mapManager(nullptr) {
    eventMediator = new GameEventMediator();
    physicsEngine = new PhysicsEngine();
    player = new Mario(
        // Starting position
        sf::Vector2f(400.f, 500.f), 
        // Size
        sf::Vector2f(64.f, 64.f),   
        // Health
        100,  
        // Speed
        20.0f                      
    );
	player->movementComponent->onGround = false;
    Enemies.clear();
	Blocks.clear();

    // Add Mario to game objects
    // gameObjects.push_back(player);

    levelGUI = new LevelGUI();
}


GameState::~GameState() {
    // Clean up all game objects
 
    delete mapManager;
    delete physicsEngine;
    delete eventMediator;
    delete player;
    for (auto& enemy : Enemies) {
		delete enemy;
	}
}

void GameState::loadLevel(int level) {
    if (mapManager) {
        delete mapManager;
    }

    mapManager = new MapManager();
    if (level == 1) {
        mapManager->loadMap("Level1_Map", player, Enemies, Blocks, window);
    }
    else if (level == 2) {
        //mapManager->loadMap("Level2_Map");
    }
    else if (level == 3) {
        //mapManager->loadMap("Level3_Map");
    }
    initGameEventMediator();
}

void GameState::initGameEventMediator() {
    player->setEventMediator(eventMediator);
    eventMediator->addPlayer(player);
    for (auto& enemy : Enemies) {
        enemy->setEventMediator(eventMediator);
        eventMediator->addEnemy(enemy);
    }
    for (auto& Block : Blocks) {
        Block->setEventMediator(eventMediator);
        eventMediator->addBlock(Block);
    }
    eventMediator->addPhysicsEngine(physicsEngine);
    physicsEngine->setEventMediator(eventMediator);

}


void GameState::update(const float& dt) {
    if (mapManager) {
		mapManager->update(dt, player);
    }
    /*
    Process: 
    1. Handle input from user
    2. Update animations of entities (Blocks, Enemies, Player)
    2. Update movements of all entities (Update velocity + apply external forces)
    3. Check for collisions
    4. Update Game Events
    */
    eventMediator->updateInput(dt);
    eventMediator->updateAnimations(dt);
    eventMediator->updateMovements(dt);
    eventMediator->resolveCollision(dt);
    //resolveCollision(dt);
       
    // Update physics first
    // physicsEngine.playerUpdatePhysics(dt);
    // physicsEngine.objectUpdatePhysics(dt);
    
    levelGUI->updateInfo(player->getHealth(), 10);  
    sf::View view = window->getView();
    levelGUI->updatePosition(view);
    // Then update all game objects
}
  
void GameState::render(sf::RenderTarget* target) {
    if (!target) {
        target = window;
    }

    if (mapManager) {
        //mapManager->render();
    }
    cerr << player->hitbox.getPosition().x << endl;
    player->render(target);
	
    levelGUI->render(target);

    for (auto& Block : Blocks) {
        Block->render(target);
    }
	//cerr << Blocks.size() << endl;
}

