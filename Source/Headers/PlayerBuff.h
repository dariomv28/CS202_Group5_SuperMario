#pragma once
#include "PlayerManager.h"

class PlayerBuff
{
protected:
	std::string type;
public:
	//PlayerBuff();
	virtual void applyBuff(GameEventMediator* eventMediator) = 0;
	std::string getType();
};

