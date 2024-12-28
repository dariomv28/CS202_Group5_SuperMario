#pragma once
#include "Enemy.h"
class Bowser :
    public Enemy
{
private:
    const float reloadDuration = 12.f;

	// Movement and positioning
	float walkSpeed;
	float x_min = 32.0f;
	float x_max = 13416.0f;

	bool isAlive;

	// Animation sprite sheet
	std::unordered_map<std::string, sf::IntRect> spritesSheet;

	// Current action string
	std::string currentAction;
	bool isAnimationInProgress;

	// skill
	std::string currentSkill;

	// Shooting
	const float reloadFire = 5.0f;
	float reloadTimer;
	// skill
	int skill;
	const float skillDuration = 20.0f;
	const float animationtime = 3.0f;
	float skillTimer;
	int stepAnimationSkill = 0;
	float AnimationTimer;
	bool doneAnimation = false;
	bool doingAnimation = false;
		// blind
		const float blindDuration = 15.0f;
		float blindTimer;
		// render enemies


		

	void initAnimations();
public:
    Bowser();
	Bowser(sf::Vector2f position, sf::Vector2f size, float x_min = 32.0f, float x_max = 13416.0f);
	~Bowser();

    void updateAnimation(const float& dt) override;

    // Update function
    void update(const float& dt) override;
    void getDamaged() override;
	void updateShooting(const float& dt);

    // Collision response
    void move(const float& dt) override;
    void reactToPlayerCollision(int collidedSide) override;
    void reactToBlockCollision(int collidedSide) override;

	//void summonMinions(); //Summon Goombas and Koopa
	///void summonCircleFireballs();
	//void summon
	void updateSkill_1(const float& dt);
	void updateSkill_2(const float& dt);

	void setIsAlive(bool alive) override;
	bool getIsAlive() const override;
};

