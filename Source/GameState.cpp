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
        3,  
        // Speed
        16.0f                     
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
        mapManager->loadMap("Level1_Map", player, Enemies, Blocks, PowerUps, window);

        // Fixed boundaries
        Enemies.push_back(new Goomba(sf::Vector2f(300.f, 500.f), sf::Vector2f(64.f, 64.f)));
        Enemies.push_back(new Goomba(sf::Vector2f(700.f, 500.f), sf::Vector2f(64.f, 64.f)));
        
        Enemies.push_back(new Goomba(sf::Vector2f(2096.f, 500.f), sf::Vector2f(64.f, 64.f)));

        Enemies.push_back(new Goomba(sf::Vector2f(2777.f, 500.f), sf::Vector2f(64.f, 64.f)));

        Enemies.push_back(new Goomba(sf::Vector2f(3279.f, 500.f), sf::Vector2f(64.f, 64.f)));

        Enemies.push_back(new Goomba(sf::Vector2f(9327.f, 500.f), sf::Vector2f(64.f, 64.f)));

        Enemies.push_back(new Goomba(sf::Vector2f(10269.f, 500.f), sf::Vector2f(64.f, 64.f)));

        Enemies.push_back(new Goomba(sf::Vector2f(10960.f, 500.f), sf::Vector2f(64.f, 64.f)));

        Enemies.push_back(new Goomba(sf::Vector2f(12370.f, 500.f), sf::Vector2f(64.f, 64.f)));

        Enemies.push_back(new Goomba(sf::Vector2f(13098.f, 500.f), sf::Vector2f(64.f, 64.f)));

        // Customized boundaries
        Enemies.push_back(new Goomba(sf::Vector2f(4700.f, 500.f), sf::Vector2f(64.f, 64.f), 4528.f, 5432.f));

        Enemies.push_back(new Goomba(sf::Vector2f(5200.f, 195.f), sf::Vector2f(64.f, 64.f), 5100.f, 5600.f));

        Enemies.push_back(new Goomba(sf::Vector2f(5945.f, 195.f), sf::Vector2f(64.f, 64.f), 5800.f, 6050.f));

        Enemies.push_back(new Goomba(sf::Vector2f(5800.f, 500.f), sf::Vector2f(64.f, 64.f), 5739.f, 8511.f));
        Enemies.push_back(new Goomba(sf::Vector2f(7000.f, 500.f), sf::Vector2f(64.f, 64.f), 5739.f, 8511.f));

        Enemies.push_back(new Goomba(sf::Vector2f(8348.f, 195.f), sf::Vector2f(64.f, 64.f), 8180.f, 8408.f));   

        Enemies.push_back(new Goomba(sf::Vector2f(10900.f, 450.f), sf::Vector2f(64.f, 64.f), 10718.f, 10978.f));
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

    for (auto& Block : Blocks) {
		Block->setEventMediator(eventMediator);
	}
    for (auto& Enemy : Enemies) {
        Enemy->setEventMediator(eventMediator);
    }
    for (auto& PowerUp : PowerUps) {
		PowerUp->setEventMediator(eventMediator);
	}
    levelGUI->setEventMediator(eventMediator);
    physicsEngine->setEventMediator(eventMediator);

    eventMediator->addPlayer(player);
    eventMediator->addEnemy(Enemies);
    eventMediator->addBlock(Blocks);    
    eventMediator->addPhysicsEngine(physicsEngine);
    eventMediator->addLevelGUI(levelGUI);
    eventMediator->addPowerUp(PowerUps);
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
    eventMediator->updateEvents(dt);
    eventMediator->updateLevelGUI(window->getView());
    //resolveCollision(dt);
       
    // Update physics first
    // physicsEngine.playerUpdatePhysics(dt);
    // physicsEngine.objectUpdatePhysics(dt);
    
    // Then update all game objects
}
  
void GameState::render(sf::RenderTarget* target) {
    if (!target) {
        target = window;
    }

    if (mapManager) {
        //mapManager->render();
    }
    // cerr << player->hitbox.getPosition().x << endl;
    player->render(target);
	
    levelGUI->render(target);

    //Only render the blocks that are within the view
    //Get the view bounds
    sf::Vector2f viewCenter = target->getView().getCenter();
    sf::Vector2f viewSize = target->getView().getSize();

    sf::FloatRect viewBounds(viewCenter.x - viewSize.x / 2.f, viewCenter.y - viewSize.y / 2.f, viewSize.x, viewSize.y);

    std::cout << viewBounds.left << " " << viewBounds.top << " " << viewBounds.width << " " << viewBounds.height << std::endl;


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
	//cerr << Blocks.size() << endl;
}

