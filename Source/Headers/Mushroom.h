#pragma once
#include "PowerUpObject.h"

//Name = "mushroom"
class Mushroom :
    public PowerUpObject	
{
private:
    int type;
	float floatSpeed = 0.0f;
	float floatTimer = 0.0f;
public:
    Mushroom(sf::Vector2f position, sf::Vector2f size, std::string name, int type);
	~Mushroom();

	//Setters and Getters
	//void setType(int type);
	//int getType();

	void update(const float& dt);
	void reactToCollison();

	void setFloatSpeed(float speed);
};

