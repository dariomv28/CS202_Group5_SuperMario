#pragma once
#include "LivingEntity.h"

// Enemy is an abstract class 

class Enemy : public LivingEntity
{
private:

public:
	Enemy();
	Enemy(const Enemy& other);

	virtual bool getIsAlive() const = 0;
	virtual void setIsAlive(bool alive) = 0;
	virtual void getDamaged() = 0;
	virtual void reactToPlayerCollision(int collidedSide) = 0;
	virtual void reactToBlockCollision(int collidedSide) = 0;

};

