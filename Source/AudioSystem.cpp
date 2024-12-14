#include "Headers/AudioSystem.h"


AudioSystem::AudioSystem() {
	if (!music.openFromFile("Source/Resources/audio/Background Music.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_BACKGROUND_MUSIC");
	}
	if (!jumpSoundBuffer.loadFromFile("Source/Resources/audio/Jump.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_JUMP_SOUND_EFFECT");
	}
	if (!buttonSoundBuffer.loadFromFile("Source/Resources/audio/Button.mp3")) {
		throw("ERROR::AUDIOSYSTEM::CANNOT_LOAD_JUMP_SOUND_EFFECT");
	}
	jumpSound.setBuffer(jumpSoundBuffer);
	buttonSound.setBuffer(buttonSoundBuffer);
}

void AudioSystem::playMusic() {
	music.setLoop(true);
	music.play();
}

void AudioSystem::playJumpSound() {
	jumpSound.play();
}

void AudioSystem::playbuttonSound() {
	buttonSound.play();
}