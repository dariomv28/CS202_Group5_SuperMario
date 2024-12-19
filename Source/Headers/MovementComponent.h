#pragma once

#include "stdafx.h"
#include "GameEventMediator.h"

class MovementComponent
{
private:
	int jumpsRemaining;
	const int MAX_JUMPS = 2;
public:
	const float JUMP_FORCE = -900.f;
	const float MAX_FALL_SPEED = 1000.f;

	int acceleration;
	int maxVelocity;
	bool isMoveLeft;
	bool isMoveRight;
	bool isJump;
	bool onGround;
	bool hitCeiling;

	sf::Vector2f velocity;
	MovementComponent();
	MovementComponent(float a, float maxV);
	~MovementComponent();

	void moveLeft(const float& dt);
	void moveRight(const float& dt);

	void jump(const float& dt, GameEventMediator* eventMediator);

	void setmoveLeft(bool moveLeft);
	void setmoveRight(bool moveRight);

	void resetJumps();
	int getJumpsRemaining() const;
};