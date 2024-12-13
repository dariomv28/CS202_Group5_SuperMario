#pragma once
#include "stdafx.h"
class AudioSystem
{
private:
	sf::Music music;
	sf::Sound jumpSound;
	sf::Sound buttonSound;
	sf::SoundBuffer jumpSoundBuffer;
	sf::SoundBuffer buttonSoundBuffer;
public:
	AudioSystem();
	void playMusic();
	void playSound();
	void playbuttonSound();
};

