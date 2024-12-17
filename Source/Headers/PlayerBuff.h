#pragma once
#include "PlayerManager.h"

class PlayerBuff
{
public:
	virtual void applyBuff(PlayerManager* player) = 0;
};

