#include "Headers/LevelManager.h"
#include "Headers/SolidBlock.h"
#include "Headers/Pipe.h"
#include "Headers/CoinBlock.h"

LevelManager::LevelManager() {
	map_texture.loadFromFile("Source/Resources/texture/Map.png");
	cell_sprite.setTexture(map_texture);
	CurrentLeft = 0;
	CurrentRight = SCREEN_WIDTH;
}

LevelManager::~LevelManager() {
    
}

void LevelManager::update(float dt) {
	
  
}

void LevelManager::update(Mario*& Player) {

}

void LevelManager::render() {
	
}

unsigned short LevelManager::get_map_sketch_height() const
{
	return map_sketch.getSize().y;
}

unsigned short LevelManager::get_map_sketch_width() const
{
	return map_sketch.getSize().x;
}

void LevelManager::draw_map(const bool i_draw_background, const bool i_underground, const unsigned i_view_x, sf::RenderWindow& i_window)
{
	i_window.draw(background1);
	i_window.draw(background2);
	return;
}

//void LevelManager::set_map_cell(const unsigned short i_x, const unsigned short i_y, const Cell& i_cell)
//{
//	map[i_x][i_y] = i_cell;
//}

//void LevelManager::set_map_size(const unsigned short i_new_size)
//{
//	map.clear();
//	map.resize(i_new_size);
//}

void LevelManager::update_map_sketch(const unsigned char i_current_level)
{
	map_sketch.loadFromFile("Source/Resources/texture/LevelSketch" + std::to_string(static_cast<unsigned short>(i_current_level)) + ".png");
	return;
}

void LevelManager::update_background(const unsigned char i_current_level)
{
	texture_background_1.loadFromFile("Source/Resources/texture/background_level" + std::to_string(static_cast<unsigned short>(i_current_level)) + "_1.png");
	background1.setTexture(texture_background_1);
	texture_background_2.loadFromFile("Source/Resources/texture/background_level" + std::to_string(static_cast<unsigned short>(i_current_level)) + "_2.png");
	background2.setTexture(texture_background_2);
	background1.setPosition(0, 0);
	background2.setPosition(0, 0);
	/*i_level_manager.get_map_sketch_width()
	i_level_manager.get_map_sketch_height() / 3.f*/
	background1.setScale((get_map_sketch_width() * 64) / background1.getTexture()->getSize().x, (get_map_sketch_height()*64 / 3.f) / background1.getTexture()->getSize().y);
	background2.setScale((get_map_sketch_width() * 64) / background2.getTexture()->getSize().x, (get_map_sketch_height() * 64 / 3.f) / background2.getTexture()->getSize().y);
}


sf::Color LevelManager::get_map_sketch_pixel(const unsigned short i_x, const unsigned short i_y) const {
	/*if (i_x >= map_sketch.getSize().x || i_y >= map_sketch.getSize().y) {
		throw std::out_of_range("Pixel coordinates are out of bounds");
	}*/
	return map_sketch.getPixel(i_x, i_y);
}



void convert_sketch(const unsigned char i_current_level, unsigned short& i_level_finish, 
	vector<Enemy*>& i_enemies, vector<Block*> &Blocks, vector<PowerUpObject*>& PowerUp,
	sf::Color& i_background_color, LevelManager& i_level_manager, Mario& i_mario)
{
	unsigned short map_height;
	i_level_manager.update_map_sketch(i_current_level);
	//i_level_manager.set_map_size(i_level_manager.get_map_sketch_width());

	//We divide the height by 3 because the sketch stores the level as 3 layers: blocks, entities, and background tiles.
	map_height = floor(i_level_manager.get_map_sketch_height() / 3.f);
	i_level_manager.update_background(i_current_level);


	// get map_sketch's begining point on x-axis
	unsigned short x = i_level_manager.get_map_sketch_width() - 1;
	i_background_color = i_level_manager.get_map_sketch_pixel(0, i_level_manager.get_map_sketch_height() - 1);

	for (unsigned short a = 0; a < i_level_manager.get_map_sketch_width(); a++)
	{
		for (unsigned short b = 0; b < 2 * map_height; b++)
		{
			sf::Color pixel = i_level_manager.get_map_sketch_pixel(a, b);

			if (b < map_height)
			{
				
				if (pixel == sf::Color(255, 200, 200))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "underground_1_2"));
				else if (pixel == sf::Color(220, 220, 220))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "ground_1_2"));
				else if (pixel == sf::Color(240, 240, 240))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "ground_1_1"));
				else if (pixel == sf::Color(255, 225, 225))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "underground_1_1"));
				else if (pixel == sf::Color(200, 200, 200))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "ground_1_3"));
				else if (pixel == sf::Color(255, 175, 175))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "underground_1_3"));
				else if (pixel == sf::Color(193, 113, 52))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "wall_1"));
				else if (pixel == sf::Color(146, 73, 0))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "brick_1"));
				else if (pixel == sf::Color(146, 73, 50))
					Blocks.push_back(new CoinBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "coin_block"));
				else if (pixel == sf::Color(0, 255, 0))
					Blocks.push_back(new Pipe(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE * 2, CELL_SIZE * 3), "pipe", 3));
				else if (pixel == sf::Color(0, 253, 0))
					Blocks.push_back(new Pipe(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE * 2, CELL_SIZE * 2), "pipe", 2));
	
				//if (sf::Color(182, 73, 0) == pixel)
				//{
				//	i_level_manager.set_map_cell(a, b, Cell::Brick);
				//}
				//else if (sf::Color(255, 255, 0) == pixel)
				//{
				//	i_level_manager.set_map_cell(a, b, Cell::Coin);
				//}
				//else if (sf::Color(0, 146, 0) == pixel || sf::Color(0, 182, 0) == pixel || sf::Color(0, 219, 0) == pixel)
				//{
				//	//Multiple colors, because we need to know which part of the pipe we need to draw.
				//	i_level_manager.set_map_cell(a, b, Cell::Pipe);
				//}
				//else if (sf::Color(255, 73, 85) == pixel || sf::Color(255, 146, 85) == pixel)
				//{
				//	i_level_manager.set_map_cell(a, b, Cell::QuestionBlock);
				//}
				//else if (sf::Color(255, 200, 200) == pixel)
				//{
				//	Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "underground_1_2"));
				//	//i_level_manager.set_map_cell(a, b, Cell::Wall);
				//}
				//else if ()
				//{

				//}
				//else
				//{
				//	i_level_manager.set_map_cell(a, b, Cell::Empty);

				//	if (sf::Color(0, 255, 255) == pixel)
				//	{
				//		i_level_finish = a;
				//	}
				//}
			}
			else
			{
				if (sf::Color(255, 0, 0) == pixel)
				{
					i_mario.setPosition(CELL_SIZE * a, 250);
				}
				else if (sf::Color(182, 73, 0) == pixel)
				{
					//i_enemies.push_back(std::make_shared<Goomba>(sf::Color(0, 0, 85) == i_background_color, CELL_SIZE * a, CELL_SIZE * (b - map_height)));
				}
				else if (sf::Color(0, 219, 0) == pixel)
				{
					//i_enemies.push_back(std::make_shared<Koopa>(sf::Color(0, 0, 85) == i_background_color, CELL_SIZE * a, CELL_SIZE * (b - map_height)));
				}
			}
		}
	}
}

