#include "Headers/LV1.h"
#include <iostream>

LV1::LV1(Mario* &Player, vector<Enemy*> &Enemies, sf::RenderWindow *window) {
	BackGroundColor = sf::Color::Black;
	View = sf::View(sf::FloatRect(0, 0, 1560, 960));
	view_x = 0;
	this->window = window;
	FinishLevel = 0;
	convert_sketch(0, FinishLevel, Enemies, BackGroundColor, *this, *Player);
}

LV1::~LV1() {
  
}

void LV1::loadLevel() {
    //convert_sketch(0, 0,i_enemies, sf::Color & i_background_color, LevelManager & i_level_manager, Mario & i_mario)
}

void LV1::update(float dt) {
	View.move(2, 0);
	view_x += 2;
	window->setView(View);

}

void LV1::render() {
	//this->draw_map(true, false, 0, *window);
	this->draw_map(true, false , view_x, *window);
	//this->draw_map(false, true, 0, *window);
	
	this->draw_map(false, false, view_x, *window);
}


