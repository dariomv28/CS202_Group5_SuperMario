#pragma once
#include "stdafx.h"

//Movement caused by the object itself (user input, AI, etc.)
class MovementComponent
{
private:
	const float PIXELS_PER_METER = 16.0f;
	int jumpsRemaining;
	const int MAX_JUMPS = 2;
public:
	int acceleration;
	int maxVelocity;
	bool isMoveLeft;
	bool isMoveRight;
	bool isJump;
	bool onGround;
	bool hitCeiling;

	sf::Vector2f velocity;
	MovementComponent();
	MovementComponent(int a, int maxV);
	~MovementComponent();

	void moveLeft(const float& dt);
	void moveRight(const float& dt);
	void jump(const float& dt);

	void resetJumps();
	int getJumpsRemaining() const;
};