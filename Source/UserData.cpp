#include "Headers/UserData.h"
#include "Headers/Mario.h"
#include "Headers/Character.h"


UserData::UserData()
{
	name = "NoName";
	player.assign(4, nullptr);
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

void UserData::createPlayer() {
	player[1] = Character::createPlayer(nameCharacter);
	player[2] = Character::createPlayer(nameCharacter);
	player[3] = Character::createPlayer(nameCharacter);
}


void UserData::resetPlayer(int world)
{
	player[world] = nullptr;

	player[1] = Character::createPlayer(nameCharacter);
	player[world] = Character::createPlayer(nameCharacter);

}

void UserData::setPlayer(int world, PlayerManager* player)
{
	this->player[world] = player;
}

PlayerManager* UserData::getPlayer(int world)
{
	return player[world];
}

PlayerManager* UserData::getClonePlayer(int world)
{
	PlayerManager* clonePlayer = nullptr;
	if (nameCharacter == "Mario") {
		clonePlayer = new Mario();
	}
	else {
		clonePlayer = new Luigi();
	}

	clonePlayer->setHealth(player[world]->getHealth());
	clonePlayer->setBig(player[world]->getBig());

	return clonePlayer;
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

void UserData::setNameCharacter(const std::string& name) {
	nameCharacter = name;
}

std::string UserData::getNameCharacter() const {
	return nameCharacter;
}

void UserData::saveData() {
	std::ofstream file("SaveData.txt");
	//Save the user's name
	file << name << std::endl;

	//Save the name character
	file << nameCharacter << std::endl;

	//Save the player
	for (int i = 1; i <= 3; i++) {
		file << player[i]->getHealth() << std::endl;
		file << player[i]->getBig() << std::endl;
	}

	//Save the completed levels
	file << completed.size() << std::endl;

	for (auto& i : completed) {
		file << i.first << std::endl;
		file << i.second << std::endl;
	}

	//Save the scores
	file << score.size() << std::endl;

	for (auto& i : score) {
		file << i.first << std::endl;
		file << i.second << std::endl;
	}

	file.close();
}

void UserData::loadData() {
	std::ifstream file("SaveData.txt");
	//Load the user's name

	file >> name;
	//Load the name character

	file >> nameCharacter;

	//Load the player
	for (int i = 1; i <= 3; i++) {
		int health;
		bool big;
		file >> health;
		file >> big;
		player[i] = Character::createPlayer(nameCharacter);
		player[i]->setHealth(health);
		player[i]->setBig(big);
	}

	//Load the completed levels
	int size;
	file >> size;
	for (int i = 0; i < size; i++) {
		std::string key;
		bool value;
		file >> key;
		file >> value;
		completed[key] = value;
	}

	//Load the scores
	file >> size;
	for (int i = 0; i < size; i++) {
		std::string key;
		long long value;
		file >> key;
		file >> value;
		score[key] = value;
	}


	file.close();
}
