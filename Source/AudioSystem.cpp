#include "Headers/AudioSystem.h"


AudioSystem::AudioSystem() {
	if (!music.openFromFile("Source/Resources/audio/BackGround Music.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_BACKGROUND_MUSIC");
	}
	if (!jumpSoundBuffer.loadFromFile("Source/Resources/audio/Jump.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_JUMP_SOUND_EFFECT");
	}
	//if (!buttonSoundBuffer.loadFromFile("Source/Resources/audio/Button.mp3")) {
		//throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_JUMP_SOUND_EFFECT");
	//}
	if (!level1Music.openFromFile("Source/Resources/audio/Level 1.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_LEVEL_1_MUSIC");
	}
	if (!level2Music.openFromFile("Source/Resources/audio/Level 2.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_LEVEL_2_MUSIC");
	}
	if (!level3Music.openFromFile("Source/Resources/audio/Level 3.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_LEVEL_3_MUSIC");
	}
	jumpSound.setBuffer(jumpSoundBuffer);
	buttonSound.setBuffer(buttonSoundBuffer);
}

void AudioSystem::playMusic() {
	music.setLoop(true);
	music.play();
}

void AudioSystem::stopMusic() {
	music.stop();
}

void AudioSystem::playLevel1Music() {
	level1Music.setLoop(true);
	level1Music.play();
}

void AudioSystem::stopLevel1Music() {
	level1Music.stop();
}

void AudioSystem::playLevel2Music() {
	level2Music.setLoop(true);
	level2Music.play();
}

void AudioSystem::stopLevel2Music() {
	level2Music.stop();
}

void AudioSystem::playLevel3Music() {
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