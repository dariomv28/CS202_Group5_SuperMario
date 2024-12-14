#pragma once
#include "stdafx.h"

class PlayerManager;
class LivingEntity;
class Enemy;
class Block;
class GameObject;
class PhysicsEngine;
class LevelGUI;
class PowerUpObject;
class AudioSystem;

class GameEventMediator
{
private:
	//Pointers to the original objects
	PhysicsEngine* physicsEngine;
	PlayerManager* player;
	std::vector<Block*>* blocks;
	std::vector<Enemy*>* enemies;
	std::vector<PowerUpObject*>* PowerUps;
	LevelGUI* levelGUI;
	AudioSystem* audio;
public:
	// Initialization function
	GameEventMediator();
	~GameEventMediator();
	void addPlayer(PlayerManager* player);
	void addBlock(std::vector<Block*>& blocks);
	void addEnemy(std::vector<Enemy*>& enemies);
	void addPhysicsEngine(PhysicsEngine* physicsEngine);
	void addLevelGUI(LevelGUI* levelGUI);
	void addPowerUp(std::vector<PowerUpObject*>& PowerUps);
	void addAudioSystem(AudioSystem* audio);

	// Physics Engine functions
	void applyExternalForce(LivingEntity* entity, const float& dt);
	void resolveCollision(const float& dt);
	
	// Update functions
	void updateInput(const float& dt);
	void updateEvents(const float& dt);
	void updateLevelGUI(const sf::View& view);

	// LevelGUI events
	void increaseCoins(int numCoins);
	void increaseScore(int numScore);
	void updateHealth(); // For LevelGUI
	
	// Player events
	void setPlayerBig(bool big);
	void decreasePlayerHealth();
	void pushPlayerLeft();
	void pushPlayerRight();

	// PowerUp events
	void spawnPowerUp(PowerUpObject* PowerUp);

	// Object deletion functions
	void defeatPlayer();
	void deleteEnemy(Enemy* enemy);
	void deleteBlock(Block* block);
	void deletePowerUp(PowerUpObject* PowerUp);

	// Audio events
	void playMenuMusic();
	void playLevelMusic(int level);
	void playLevel1Music();
	void playLevel2Music();
	void playLevel3Music();

	void playButtonSound();
	void playCoinSound();
	void playJumpSound();
	void playBrickDestroyedSound();
};

