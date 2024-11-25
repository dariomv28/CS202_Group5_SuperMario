#pragma once
#include "LivingEntity.h"

class Enemy : public LivingEntity
{
private:

public:
	Enemy();
	Enemy(const Enemy& other);
	virtual void update() = 0;

};

