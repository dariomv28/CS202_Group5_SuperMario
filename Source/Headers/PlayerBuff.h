#pragma once
#include "PlayerManager.h"

class PlayerBuff
{
public:
	//PlayerBuff();
	virtual void applyBuff(PlayerManager* player, GameEventMediator* eventMediator) = 0;
};

