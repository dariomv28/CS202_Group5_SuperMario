#pragma once
#include "PlayerBuff.h"
class FireBuff :
    public PlayerBuff
{
private:
    sf::Clock reloadTimer;
    const float reloadTime = 0.35f;
    int direction;
public:
    FireBuff();
	virtual ~FireBuff();

	void applyBuff(GameEventMediator* eventMediator) override;
};

