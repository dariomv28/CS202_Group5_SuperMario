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
	virtual void moveWithView(const float& dt, const sf::View& view);
};

