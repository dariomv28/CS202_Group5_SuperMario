#pragma once
#include "stdafx.h"
#include "PlayerManager.h"


class UserData
{
private:
	std::string name;
	std::string nameCharacter;
	std::vector<PlayerManager*> player;
	std::unordered_map<std::string, long long> score;
	std::unordered_map<std::string, bool> completed;
	
public:
	UserData();
	~UserData();

	//Setters and Getters
	void setName(std::string name);
	std::string getName();

	void resetPlayer(int world);
	void setPlayer(int world, PlayerManager* player);
	PlayerManager* getPlayer(int world);
	PlayerManager* getClonePlayer(int world);

	void setScore(int world, int level, long long score);
	long long getScore(int world, int level);
	

	bool getCompleted(int world, int level);
	void setCompleted(int world, int level, bool complete);
	void setNameCharacter(const std::string& name);
	std::string getNameCharacter() const;
	void createPlayer();

	void saveData();
	void loadData();
	
	void saveCSV();
};

