#pragma
#ifndef LEVELMANAGER_H
#define LEVELMANAGER_H

#include "stdafx.h"
#include "Enemy.h"
#include "Mario.h"
#include "Block.h"
using namespace std;

class LevelManager {
public:
    LevelManager();
    virtual ~LevelManager();

    virtual void loadLevel() = 0;
    virtual void update(float dt);
	virtual void update(Mario*& Player);
    virtual void render();  

    // new
	unsigned short get_map_sketch_height() const;
	unsigned short get_map_sketch_width() const;
	//unsigned short get_map_width() const;

	//void add_brick_particles(const unsigned short i_x, const unsigned short i_y);
	//void add_question_block_coin(const unsigned short i_x, const unsigned short i_y);
	void draw_map(const bool i_draw_background, const bool i_underground, const unsigned i_view_x, sf::RenderWindow& i_window);
	//void set_map_cell(const unsigned short i_x, const unsigned short i_y, const Cell& i_cell);
	//void set_map_size(const unsigned short i_new_size);
	//virtual void update();
	void update_map_sketch(const unsigned char i_current_level);

	//std::vector<unsigned char> map_collision(const std::vector<Cell>& i_check_cells, const sf::FloatRect& i_hitbox) const;
	//std::vector<unsigned char> map_collision(const std::vector<Cell>& i_check_cells, std::vector<sf::Vector2i>& i_collision_cells, const sf::FloatRect& i_hitbox) const;

	sf::Color get_map_sketch_pixel(const unsigned short i_x, const unsigned short i_y) const;

protected:
	std::vector<Object> brick_particles;
	std::vector<Object> question_block_coins;

	sf::Color BackGroundColor;
	unsigned short FinishLevel;

	sf::Image mapSketch;
	sf::Sprite cellSprite;
	sf::Texture mapTexture;

	sf::Image map_sketch;

	sf::Sprite cell_sprite;

	sf::RenderWindow* window;

	sf::Texture map_texture;
	//Animation coin_animation;
	//Animation question_block_animation;
	sf::View View;
	float view_x;
	//Map map;
	
	float CurrentLeft;
	float CurrentRight;

	float ConstantLeft;
	float ConstantRight;
    
};

void convert_sketch(const unsigned char i_current_level, unsigned short& i_level_finish, vector<Enemy*>& i_enemies, vector<Block*>& Blocks, sf::Color& i_background_color, LevelManager& i_level_manager, Mario& i_mario);

#endif 
