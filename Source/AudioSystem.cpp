#include "Headers/AudioSystem.h"


AudioSystem::AudioSystem() {
	if (!music.openFromFile("Source/Resources/audio/BackGround Music.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_BACKGROUND_MUSIC");
	}
	if (!jumpSoundBuffer.loadFromFile("Source/Resources/audio/Jump.wav")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_JUMP_SOUND_EFFECT");
	}
	if (!buttonSoundBuffer.loadFromFile("Source/Resources/audio/buttonSound.wav")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_JUMP_SOUND_EFFECT");
	}
	if (!coinSoundBuffer.loadFromFile("Source/Resources/audio/coin.wav")) {
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
	//if (!level3Music.openFromFile("Source/Resources/audio/Level 3.mp3")) {
		//throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_LEVEL_3_MUSIC");
	//}
	jumpSound.setBuffer(jumpSoundBuffer);
	buttonSound.setBuffer(buttonSoundBuffer);
	coinSound.setBuffer(coinSoundBuffer);
	brickSound.setBuffer(brickSoundBuffer);
}

void AudioSystem::playMusic() {
	stopAllMusic();
	music.setLoop(true);
	music.play();
}

void AudioSystem::stopMusic() {
	music.stop();
}

void AudioSystem::playLevel1Music() {
	stopAllMusic();
	level1Music.setLoop(true);
	level1Music.play();
}

void AudioSystem::stopLevel1Music() {
	level1Music.stop();
}

void AudioSystem::playLevel2Music() {
	stopAllMusic();
	level2Music.setLoop(true);
	level2Music.play();
}

void AudioSystem::stopLevel2Music() {
	level2Music.stop();
}

void AudioSystem::playLevel3Music() {
	stopAllMusic();
	level3Music.setLoop(true);
	level3Music.play();
}

void AudioSystem::stopLevel3Music() {
	level3Music.stop();
}

void AudioSystem::playJumpSound() {
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
	brickSound.play();
}