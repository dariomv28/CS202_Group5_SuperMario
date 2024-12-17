#include "Headers/FireBuff.h"

FireBuff::FireBuff() {
}

FireBuff::~FireBuff() {
}

void FireBuff::applyBuff(PlayerManager* player) {
	if (reloadTimer.getElapsedTime().asSeconds() >= reloadTime) {
		reloadTimer.restart();
		//Spawn Bullet
	}
}
