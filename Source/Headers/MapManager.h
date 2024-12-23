#pragma once

#include "WinFlag.h"
#include "Enemy.h"
#include "Mario.h"
#include "Block.h"
#include "PowerUpObject.h"
#include "SolidBlock.h"
#include "Pipe.h"
#include "CoinBlock.h"
#include "Coin.h"
#include "Goomba.h"
#include "Koopa.h"
#include "Brick.h"
#include "MushroomBlock.h"
#include "Lava.h"
#include "Trampoline.h"
#include "Cannon.h"
#include "CloudBlock.h"

using namespace std;

class MapManager {
protected:
	unordered_map<string, string> styles;
	unordered_map<string, string> pipe_styles;
	unordered_map<string, string> background_styles;

	sf::Image map_sketch;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;

	sf::View View;
	sf::RenderWindow* window;
	float view_x;

	float CurrentLeft;
	float CurrentRight;

	float ConstantLeft;
	float ConstantRight;

	int currentWorld;
	int currentLevel;

public:
    MapManager(sf::RenderWindow* window);
    virtual ~MapManager();

	void initStyle();

    virtual void update(PlayerManager* player, float dt);
	virtual void updateView(PlayerManager* Player, float dt);

    // Setters and Getters
	unsigned short get_map_sketch_height() const;
	unsigned short get_map_sketch_width() const;

	void draw_map(sf::RenderTarget* target);
	void get_map_sketch(const unsigned int world, const unsigned int level);
	void update_background(const unsigned int world, const unsigned int level);
	void convert_sketch(const unsigned int world, const unsigned int level, vector<Enemy*>& i_enemies, 
		vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, PlayerManager* i_mario);

	sf::Color get_map_sketch_pixel(const unsigned short i_x, const unsigned short i_y) const;
};



