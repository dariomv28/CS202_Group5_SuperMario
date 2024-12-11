#pragma
#ifndef MAPMANAGER_H
#define MAPMANAGER_H

#include "stdafx.h"
#include "Enemy.h"
#include "Mario.h"
#include "Block.h"
#include "PowerUpObject.h"
using namespace std;

class MapManager {
public:
    MapManager(sf::RenderWindow* window);
    virtual ~MapManager();

    virtual void update(float dt);
	virtual void update(PlayerManager* Player, sf::RenderWindow* window);
    virtual void render();  

    // Setters and Getters
	unsigned short get_map_sketch_height() const;
	unsigned short get_map_sketch_width() const;

	void draw_map(sf::RenderWindow* i_window);
	void get_map_sketch(const unsigned int i_current_level);
	void update_background(const unsigned int i_current_level);
	void convert_sketch(const unsigned int i_current_level, vector<Enemy*>& i_enemies, 
		vector<Block*>& Blocks, vector<PowerUpObject*>& PowerUp, PlayerManager* i_mario);

	sf::Color get_map_sketch_pixel(const unsigned short i_x, const unsigned short i_y) const;

protected:

	sf::Image map_sketch;
	sf::Texture backgroundTexture;
	sf::Sprite backgroundSprite;
	//sf::Sprite cell_sprite;

	sf::View View;
	sf::Texture map_texture;
	//Animation coin_animation;
	//Animation question_block_animation;
	sf::RenderWindow* window;
	float view_x;
	//Map map;
	
	float CurrentLeft;
	float CurrentRight;

	float ConstantLeft;
	float ConstantRight;
    
};


#endif 
