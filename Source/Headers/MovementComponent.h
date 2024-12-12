#pragma once
#include "stdafx.h"

class MovementComponent
{
private:
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