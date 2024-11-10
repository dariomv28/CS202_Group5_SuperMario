#pragma once
#include "GameObject.h"

class Enemy : public GameObject
{
private:
	std::string type;
	bool isDefeated;
public:
	Enemy() {};
	Enemy(const Enemy& other);
	Enemy(std::string type, bool isDefeated);
	void move() override;
	void attack();
	void takeDamage();
	void respawn();
	void update();


};

