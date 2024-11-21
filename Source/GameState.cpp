#include "Headers/GameState.h"
#include <algorithm>
using namespace std;

GameState::GameState(StateData* stateData) : State(stateData), mapManager(nullptr) {
    player = new Mario(
        sf::Vector2f(400.f, 300.f),  // Starting position
        sf::Vector2f(64.f, 64.f),    // Size
        100,                         // Health
        200,                         // Speed
        &physicsEngine              // Pointer to physics engine
    );
    Enemies.clear();

    physicsEngine.addPlayer(player);
 
    // Add Mario to game objects
  //  gameObjects.push_back(player);
}


GameState::~GameState() {
    // Clean up all game objects
    for (auto& object : gameObjects) {
        delete object;
    }
    gameObjects.clear();

    delete mapManager;
}

void GameState::loadLevel(int level) {
    if (mapManager) {
        delete mapManager;
    }

    mapManager = new MapManager();
    if (level == 1) {
        mapManager->loadMap("Level1_Map", player, Enemies, window);

        // You might want to set Mario's initial position based on the level
        //player->setPosition(400.f, 500.f); // Assump that the ground is at 500.f (y)

    }
    else if (level == 2) {
        //mapManager->loadMap("Level2_Map");
    }
    else if (level == 3) {
        //mapManager->loadMap("Level3_Map");
    }

    // Add level objects to physics engine
    // mapManager->getPhysicsObjects() might return vector of GameObjects
    /*for (auto& obj : mapManager->getPhysicsObjects()) {
        physicsEngine.addObject(obj);
    }*/
}


void sleepOneSecond() {
    std::this_thread::sleep_for(std::chrono::seconds(1/3));
}

void GameState::update(const float& dt) {
    if (mapManager) {
        mapManager->update(dt);
    }
    player->update(dt);
       
    // Update physics first
    // physicsEngine.playerUpdatePhysics(dt);
    // physicsEngine.objectUpdatePhysics(dt);

    // Then update all game objects
    for (auto& object : gameObjects) {
        object->update(dt);
    }
}
  

void GameState::render(sf::RenderTarget* target) {
    if (!target) {
        target = window;
    }

    if (mapManager) {
        mapManager->render();
    }

    player->render(target);
	

    for (auto& object : gameObjects) {
        object->render(target);
    }
}

