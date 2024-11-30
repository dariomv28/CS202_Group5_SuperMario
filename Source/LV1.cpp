#include "Headers/LV1.h"
#include <iostream>

LV1::LV1(Mario* &Player, vector<Enemy*> &Enemies, vector<Block*>& Blocks, sf::RenderWindow *window) {
	BackGroundColor = sf::Color::Black;
	View = sf::View(sf::FloatRect(0, 0, 1560, 960));
	view_x = 0;
	this->window = window;
	FinishLevel = 0;
	convert_sketch(0, FinishLevel, Enemies, Blocks, BackGroundColor, *this, *Player);
}

LV1::~LV1() {
  
}


void LV1::loadLevel() {
    //convert_sketch(0, 0,i_enemies, sf::Color & i_background_color, LevelManager & i_level_manager, Madrio & i_mario)
}

void LV1::update(Mario*& Player) {
	ConstantLeft = CurrentLeft + (SCREEN_WIDTH * 5.0) / 10.0;
	ConstantRight = CurrentLeft + (SCREEN_WIDTH * 5.0) / 10.0;

	//cerr << (map_sketch.getSize().x - 1) * CELL_SIZE * 4 << endl;

	if (Player->getVelocity().x < 0 && Player->getPosition().x < ConstantLeft && CurrentLeft - abs(Player->getVelocity().x) >= 0) {
		view_x -= abs(Player->getVelocity().x);
		View.move(-abs(Player->getVelocity().x), 0);
		CurrentLeft -= abs(Player->getVelocity().x);
		CurrentRight -= abs(Player->getVelocity().x);

	}
	else if (Player->getVelocity().x > 0 && Player->getPosition().x > ConstantRight 
			&& CurrentRight + abs(Player->getVelocity().x) <= (map_sketch.getSize().x - 1) * 64) {
		view_x += abs(Player->getVelocity().x);
		View.move(abs(Player->getVelocity().x), 0);

		CurrentLeft += abs(Player->getVelocity().x);
		CurrentRight += abs(Player->getVelocity().x);
	}


	window->setView(View);
}


void LV1::render() {
	//this->draw_map(true, false, 0, *window);
	this->draw_map(true, false , view_x, *window);
	//this->draw_map(false, true, 0, *window);
	
	this->draw_map(false, false, view_x, *window);
}


