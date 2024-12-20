#include "Headers/AudioSystem.h"

AudioSystem* AudioSystem::instance = nullptr;

AudioSystem::AudioSystem() {
	init();
}


void AudioSystem::init() {
	if (!music.openFromFile("Source/Resources/audio/BackGround Music.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_BACKGROUND_MUSIC");
	}
	if (!jumpSoundBuffer.loadFromFile("Source/Resources/audio/Jump.wav")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_JUMP_SOUND_EFFECT");
	}
	if (!buttonSoundBuffer.loadFromFile("Source/Resources/audio/buttonSound.wav")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_BUTTON_SOUND_EFFECT");
	}
	if (!coinSoundBuffer.loadFromFile("Source/Resources/audio/coin.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_COIN_SOUND_EFFECT");
	}
	if (!brickSoundBuffer.loadFromFile("Source/Resources/audio/break brick.wav")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_BRICK_SOUND_EFFECT");
	}
	if (!level1Music.openFromFile("Source/Resources/audio/Level 1.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_LEVEL_1_MUSIC");
	}
	if (!level2Music.openFromFile("Source/Resources/audio/Level 2.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_LEVEL_2_MUSIC");
	}
	if (!level3Music.openFromFile("Source/Resources/audio/Level 3.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_LEVEL_3_MUSIC");
	}

	// Réglage des volumes
	music.setVolume(10.0f);
	level1Music.setVolume(10.0f);
	level2Music.setVolume(10.0f);
	level3Music.setVolume(10.0f);
	jumpSound.setBuffer(jumpSoundBuffer);
	jumpSound.setVolume(200.0f);
	buttonSound.setBuffer(buttonSoundBuffer);
	buttonSound.setVolume(200.0f);
	coinSound.setBuffer(coinSoundBuffer);
	coinSound.setVolume(200.0f);
	brickSound.setBuffer(brickSoundBuffer);
	brickSound.setVolume(200.0f);
}



void AudioSystem::playMusic() {
	if (currentBackgroundMusic == "MainMenu")
		return;
	currentBackgroundMusic = "MainMenu";
	stopAllMusic();
	music.setLoop(true);
	music.play();
}

void AudioSystem::stopMusic() {
	std::cout << "musique stop" << std::endl;
	music.stop();
}

void AudioSystem::playLevel1Music() {
	if (currentBackgroundMusic == "World1")
		return;
	currentBackgroundMusic = "World1";
	stopAllMusic();
	level1Music.setLoop(true);
	level1Music.play();
	if (!level1Music.openFromFile("Source/Resources/audio/Level1Music.wav")) {
		std::cerr << "Failed to load Level1Music.wav" << std::endl;
	}
}

void AudioSystem::stopLevel1Music() {
	level1Music.stop();
}

void AudioSystem::playLevel2Music() {
	if (currentBackgroundMusic == "World2")
		return;
	currentBackgroundMusic = "World2";
	stopAllMusic();
	level2Music.setLoop(true);
	level2Music.play();
}

void AudioSystem::stopLevel2Music() {
	level2Music.stop();
}

void AudioSystem::playLevel3Music() {
	if (currentBackgroundMusic == "World3")
		return;
	currentBackgroundMusic = "World3";
	stopAllMusic();
	level3Music.setLoop(true);
	level3Music.play();
}

void AudioSystem::stopLevel3Music() {
	level3Music.stop();
}

void AudioSystem::playJumpSound() {

if (jumpSound.getBuffer() == nullptr) {
		std::cerr << "Jump sound buffer is null! Cannot play sound." << std::endl;
		return;
}
jumpSound.play();

}

void AudioSystem::stopJumpSound() {

}

void AudioSystem::playbuttonSound() {
	buttonSound.play();
}

void AudioSystem::stopButtonSound() {

}

void AudioSystem::playCoinSound() {

	if (coinSound.getBuffer() == nullptr) {
		std::cerr << "Jump sound buffer is null! Cannot play sound." << std::endl;
		return;
	}
	coinSound.play();
}

void AudioSystem::stopCoinSound() {

}

void AudioSystem::stopAllMusic() {
	if (music.getStatus() == sf::SoundSource::Playing) {
		music.stop();
	}
	if (level1Music.getStatus() == sf::SoundSource::Playing) {
		level1Music.stop();
	}
	if (level2Music.getStatus() == sf::SoundSource::Playing) {
		level2Music.stop();
	}
	if (level3Music.getStatus() == sf::SoundSource::Playing) {
		level3Music.stop();
	}
}

void AudioSystem::setEventMediator(GameEventMediator* eventMediator) {
	this->eventMediator = eventMediator;
}

void AudioSystem::playBrickDestroyedSound() {
	if (brickSound.getBuffer() == nullptr) {
		std::cerr << "Jump sound buffer is null! Cannot play sound." << std::endl;
		return;
	}
	brickSound.play();
}

sf::Sound& AudioSystem::getJumpSound() {
	return this->jumpSound;
}

sf::SoundBuffer& AudioSystem::getJumpSoundBuffer() {
	return jumpSoundBuffer;
}

sf::SoundBuffer& AudioSystem::getButtonSoundBuffer() {
	return buttonSoundBuffer;
}

sf::SoundBuffer& AudioSystem::getCoinSoundBuffer() {
	return coinSoundBuffer;
}

sf::SoundBuffer& AudioSystem::getBrickSoundBuffer() {
	return brickSoundBuffer;
}

void AudioSystem::stop() {
	isStopped = true;
	std::cout << "AudioSystem is now stopped. Access blocked." << std::endl;
}

void AudioSystem::resume() {
	isStopped = false;
	std::cout << "AudioSystem is now active. Access restored." << std::endl;
}