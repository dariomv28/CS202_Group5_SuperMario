#pragma once
#include "LivingEntity.h"

// Enemy is an abstract class 

class Enemy : public LivingEntity
{
private:

public:
	Enemy();
	Enemy(const Enemy& other);
	virtual void update(const float& dt) = 0;

	virtual bool getIsAlive() const = 0;
	virtual void setIsAlive(bool alive) = 0;
};

