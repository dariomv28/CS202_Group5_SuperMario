#pragma once

#include "MapManager.h"
#include "stdafx.h"
#include "Enemy.h"
#include "Mario.h"
#include "Block.h"
#include "PowerUpObject.h"
#include "LevelGUI.h"
#include "GameEventMediator.h"
#include "PhysicsEngine.h"
#include "AudioSystem.h"
#include "ChatUI.h"
#include "OllamaService.h"
#include "MovingBlock.h"

class LevelManager {
protected:
    MapManager* mapManager;
    sf::RenderWindow* window;
    PlayerManager* player;
    vector<Enemy*> Enemies;
    vector<Block*> Blocks;
    vector<PowerUpObject*> PowerUps;
    LevelGUI* levelGUI;
    GameEventMediator* eventMediator;
    PhysicsEngine* physicsEngine;
    AudioSystem* audio;
    bool firstUpdate;
    bool* finishedLevel;

    ChatComponent* chatComponent = nullptr;
	LLMService* llmService = nullptr;
    ChatUI* chatUI = nullptr;

    bool chatBot = false;

public:
    LevelManager(PlayerManager* player, sf::RenderWindow* window);
    virtual ~LevelManager();
    void initGameEventMediator();
    virtual void update(const float& dt);
    virtual void render(sf::RenderTarget* target = nullptr);
    int getScore();
    bool getFinishedLevel() { return *finishedLevel; }

    void initializeChatSystem();
};

 