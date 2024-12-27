#pragma once
#include "stdafx.h"
#include "GameEventMediator.h"
class AudioSystem
{
private:
	static  AudioSystem* instance;
	sf::Music music;
	sf::Music level1Music;
	sf::Music level2Music;
	sf::Music level3Music;
	sf::Sound jumpSound;
	sf::Sound buttonSound;
	sf::Sound coinSound;
	sf::Sound brickSound;
	sf::Sound mushroomSound;
	sf::SoundBuffer jumpSoundBuffer;
	sf::SoundBuffer buttonSoundBuffer;
	sf::SoundBuffer coinSoundBuffer;
	sf::SoundBuffer brickSoundBuffer;
	sf::SoundBuffer mushroomSoundBuffer;
	std::string currentBackgroundMusic;

	bool isInitialized = false;
	bool isStopped = false;

	bool allowMusic = true;
	bool allowSound = true;

	GameEventMediator* eventMediator;
public:
	AudioSystem();
	void init();
	void playMusic();
	void stopMusic();
	void playLevel1Music();
	void stopLevel1Music();
	void playLevel2Music();
	void stopLevel2Music();
	void playLevel3Music();
	void stopLevel3Music();
	void playJumpSound();
	void stopJumpSound();
	void playbuttonSound();
	void stopButtonSound();
	void playCoinSound();
	void stopCoinSound();
	void playBrickDestroyedSound();
	void playMushroomSound();

	sf::SoundBuffer& getJumpSoundBuffer();
	sf::SoundBuffer& getButtonSoundBuffer();
	sf::SoundBuffer& getCoinSoundBuffer();
	sf::SoundBuffer& getBrickSoundBuffer();
	sf::SoundBuffer& getMushroomSoundBuffer();
	sf::Sound& getJumpSound();

	void stop();
	void resume();

	void stopAllMusic();

	void setEventMediator(GameEventMediator* eventMediator);
	void setAllowMusic(bool allowMusic);
	void setAllowSound(bool allowSound);

	bool getAllowMusic() {
		return allowMusic;
	}

	bool getAllowSound() {
		return allowSound;
	}

	static AudioSystem* getInstance() {
		if (instance == nullptr) {
			std::cout << "Creating AudioSystem instance..." << std::endl;
			instance = new AudioSystem();
		}
		return instance;
	}
};


