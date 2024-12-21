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
class MovementComponent;

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
	//MovementComponent* movementComponent;
	//LivingEntity* livingEntity;

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
	//void addMovementComponent(MovementComponent* movementComponent);
	//void addLivingEntity(LivingEntity* livingEntity);

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
	/*void updateHealth(); */
	
	// Player events
	void player2ndBuff();
	void decreasePlayerHealth();
	void increasePlayerHealth();
	void pushPlayerLeft();
	void pushPlayerRight();
	void pushPlayerUpExtra();

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

	PlayerManager*& getPlayer() { return player; }
};

