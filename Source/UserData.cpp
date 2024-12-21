#include "Headers/UserData.h"
#include "Headers/Mario.h"

UserData::UserData()
{
	player.assign(4, nullptr);
	player[1] = new Mario();
	player[2] = new Mario();
	player[3] = new Mario();
}

UserData::~UserData()
{
}

void UserData::setName(std::string name)
{
	this->name = name;
}

std::string UserData::getName()
{
	return name;
}

void UserData::resetPlayer(int world)
{
	player[world] = nullptr;
	player[world] = new Mario();
}

void UserData::setPlayer(int world, PlayerManager* player)
{
	this->player[world] = player;
}

PlayerManager* UserData::getPlayer(int world)
{
	return player[world];
}

void UserData::setScore(int world, int level, long long score)
{
	this->score["W" + std::to_string(world) + "_LV" + std::to_string(level)] = score;
}

long long UserData::getScore(int world, int level)
{
	return score["W" + std::to_string(world) + "_LV" + std::to_string(level)];
}

bool UserData::getCompleted(int world, int level)
{
	return completed["W" + std::to_string(world) + "_LV" + std::to_string(level)];
}

void UserData::setCompleted(int world, int level)
{
	completed["W" + std::to_string(world) + "_LV" + std::to_string(level)] = true;
}

