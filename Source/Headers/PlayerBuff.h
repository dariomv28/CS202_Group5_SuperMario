#pragma once
#include "PlayerManager.h"

class PlayerBuff
{
protected:
	std::string type;
public:
	//PlayerBuff();
	virtual void applyBuff(PlayerManager* player, GameEventMediator* eventMediator) = 0;
	std::string getType();
};

