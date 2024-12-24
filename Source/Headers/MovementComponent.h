#pragma once

#include "stdafx.h"
#include "GameEventMediator.h"

class MovementComponent
{
private:
	int jumpsRemaining;
public:
	float JUMP_FORCE;
	const float MAX_FALL_SPEED = 1400.f;
	int MAX_JUMPS;

	int acceleration;
	int preventFalling;
	int maxVelocity;
	bool isMoveLeft;
	bool isMoveRight;
	bool isJump;
	bool onGround;
	bool hitCeiling;

	sf::Vector2f velocity;
	MovementComponent();
	MovementComponent(float a, float maxV, int MAX_JUMPS=2, float JUMP_FORCE=-900.f);
	~MovementComponent();

	void moveLeft(const float& dt);
	void moveRight(const float& dt);

	void jump(const float& dt, GameEventMediator* eventMediator);

	void setmoveLeft(bool moveLeft);
	void setmoveRight(bool moveRight);

	void resetJumps();
	int getJumpsRemaining() const;
};