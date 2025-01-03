#pragma once

//STL
#include <algorithm>
#include <deque>
#include <iostream>
#include <map>
#include <memory>
#include <set>
#include <thread>
#include <utility>
#include <vector>
#include <list>
#include <stack>
#include <string>
#include <sstream>
#include <fstream>
#include <cmath>
#include <unordered_map>

//SFML
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>


// map manager
#include "chrono"
#include <array>
constexpr float BRICK_PARTICLE_SPEED = 4;
//A coin jumping out of the question block.
constexpr float COIN_JUMP_SPEED = -6;
constexpr float GOOMBA_SPEED = 1;
constexpr float GRAVITY = 0.25f;
constexpr float KOOPA_SHELL_SPEED = 4;
constexpr float KOOPA_SPEED = 1;
constexpr float MARIO_ACCELERATION = 0.25f;
constexpr float MARIO_JUMP_SPEED = -4;
constexpr float MARIO_WALK_SPEED = 2;
constexpr float MAX_VERTICAL_SPEED = 8;
constexpr float MUSHROOM_SPEED = 1;

constexpr unsigned char CELL_SIZE = 64;
//We use this constant when Mario is growing or when he's invincible.
constexpr unsigned char MARIO_BLINKING = 4;
//Lemme explain:
//1) Mario gets hit by an enemy.
//2) Mario looks at you like "Oh no! Me lost! Mama mia!" and pauses for this amount.
//3) Mario bounces off the screen.
constexpr unsigned char MARIO_DEATH_DURATION = 32;
constexpr unsigned char MARIO_GROWTH_DURATION = 64;
constexpr unsigned char MARIO_INVINCIBILITY_DURATION = 128;
//The longer we press the jump button, the higher Mario jumps.
constexpr unsigned char MARIO_JUMP_TIMER = 8;
constexpr unsigned char SCREEN_RESIZE = 1;

constexpr unsigned short COIN_ANIMATION_SPEED = 4;
//Since we deactivate everything outside the view, we need to have a safe area around the view where objects start updating.
constexpr unsigned short ENTITY_UPDATE_AREA = 64;
constexpr unsigned short GOOMBA_DEATH_DURATION = 32;
//Why do I have so many animation speed constants? I use them only once.
constexpr unsigned short GOOMBA_WALK_ANIMATION_SPEED = 32;
constexpr unsigned short KOOPA_GET_OUT_ANIMATION_SPEED = 4;
constexpr unsigned short KOOPA_GET_OUT_DURATION = 512;
constexpr unsigned short KOOPA_WALK_ANIMATION_SPEED = 32;
constexpr unsigned short MARIO_WALK_ANIMATION_SPEED = 4;
constexpr unsigned short QUESTION_BLOCK_ANIMATION_SPEED = 8;
constexpr unsigned short SCREEN_HEIGHT = 960;
constexpr unsigned short SCREEN_WIDTH = 1560;

constexpr std::chrono::microseconds FRAME_DURATION(16667);

enum Cell
{
	//ActivatedQuestionBlock,
	//Brick,
	//Coin,
	//Pipe,
	////Empty,
	//QuestionBlock,
	//Wall
};

enum Side {
	Collide_Top,
	Collide_Bottom,
	Collide_Left,
	Collide_Right,
	Collide_None
};

//We use this for brick particles.
//Damn, I should've called it "Particle"! I'm so dumb!
struct Object
{
	float horizontal_speed;
	float vertical_speed;
	float x;
	float y;

	Object(const float i_x, const float i_y, const float i_horizontal_speed = 0, const float i_vertical_speed = 0) :
		horizontal_speed(i_horizontal_speed),
		vertical_speed(i_vertical_speed),
		x(i_x),
		y(i_y)
	{

	}
};

typedef std::vector<std::array<Cell, SCREEN_HEIGHT / CELL_SIZE>> Map;
#include <random> 
// create the function random number in the range from x to y random by mt19937

inline int random(int x, int y)
{
	std::random_device rd;
	std::mt19937 mt(rd());
	std::uniform_int_distribution<int> dist(x, y);
	return dist(mt);
}

//#define CURL_STATICLIB
//#include "../curl/curl.h"
//
//
//#ifdef _DEBUG
//#pragma comment(lib, "../curl/libcurl_a_debug.lib")
//#else
//#pragma comment(lib, "../curl/libcurl_a.lib")
//#endif
//
//#pragma comment(lib, "Normaliz.lib")
//#pragma comment(lib, "Ws2_32.lib")
//#pragma comment(lib, "Wldap32.lib")
//#pragma comment(lib, "Crypt32.lib")
//#pragma comment(lib, "advapi32.lib")
//
//#include <nlohmann/json.hpp>