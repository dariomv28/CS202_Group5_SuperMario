#pragma once
#include "PlayerBuff.h"
class FireBuff :
    public PlayerBuff
{
private:
    sf::Clock reloadTimer;
    const float reloadTime = 0.5f;
    int direction;
public:
    FireBuff();
	virtual ~FireBuff();

	void applyBuff(PlayerManager* player, GameEventMediator* eventMediator) override;
};

