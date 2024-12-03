#include "Headers/LevelManager.h"
#include "Headers/SolidBlock.h"
#include "Headers/Pipe.h"

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

//unsigned short LevelManager::get_map_width() const
//{
//	return map.size();
//}

//void LevelManager::add_brick_particles(const unsigned short i_x, const unsigned short i_y)
//{
//	//Adding brick particles.
//	//I was too lazy to add randomness.
//	//It still looks cool, in my opinion.
//	//cerr << "!" << endl;
//	/*brick_particles.push_back(Object(i_x, i_y, -0.25f * BRICK_PARTICLE_SPEED, -1.5f * BRICK_PARTICLE_SPEED));
//	brick_particles.push_back(Object(i_x + 0.5f * CELL_SIZE, i_y, 0.25f * BRICK_PARTICLE_SPEED, -1.5f * BRICK_PARTICLE_SPEED));
//	brick_particles.push_back(Object(i_x, i_y + 0.5f * CELL_SIZE, -0.5f * BRICK_PARTICLE_SPEED, -BRICK_PARTICLE_SPEED));
//	brick_particles.push_back(Object(i_x + 0.5f * CELL_SIZE, i_y + 0.5f * CELL_SIZE, 0.5f * BRICK_PARTICLE_SPEED, -BRICK_PARTICLE_SPEED));*/
//}
//
//void LevelManager::add_question_block_coin(const unsigned short i_x, const unsigned short i_y)
//{
//	//question_block_coins.push_back(Object(i_x, i_y, 0, COIN_JUMP_SPEED));
//}

void LevelManager::draw_map(const bool i_draw_background, const bool i_underground, const unsigned i_view_x, sf::RenderWindow& i_window)
{
	//unsigned short map_end = ceil((SCREEN_WIDTH + i_view_x) / static_cast<float>(CELL_SIZE));
	//unsigned short map_height = floor(map_sketch.getSize().y / 3.f);
	//unsigned short map_start = floor(i_view_x / static_cast<float>(CELL_SIZE));

	////We're drawing the coin before drawing the blocks because we want it to appear behind the question block.
	//if (0 == i_draw_background)
	//{
	//	//for (const Object& question_block_coin : question_block_coins)
	//	{
	//		//coin_animation.set_position(question_block_coin.x, question_block_coin.y);
	//		//coin_animation.draw(i_window);
	//	}
	//}

	//for (unsigned short a = map_start; a < map_end; a++)
	//{
	//	for (unsigned short b = 0; b < map_height; b++)
	//	{
	//		unsigned short sprite_x = 0;
	//		unsigned short sprite_y = 0;

	//		cell_sprite.setPosition(CELL_SIZE * a, CELL_SIZE * b);

	//		//This code is a big mess.
	//		//But it works.
	//		//Keep that in mind before judging me.
	//		if (1 == i_draw_background)
	//		{
	//			sf::Color pixel = map_sketch.getPixel(a, b + 2 * map_height);
	//			sf::Color pixel_down = sf::Color(0, 0, 0, 0);
	//			sf::Color pixel_left = sf::Color(0, 0, 0, 0);
	//			sf::Color pixel_right = sf::Color(0, 0, 0, 0);
	//			sf::Color pixel_up = sf::Color(0, 0, 0, 0);

	//			if (255 == pixel.a)
	//			{
	//				if (0 < a)
	//				{
	//					pixel_left = map_sketch.getPixel(a - 1, b + 2 * map_height);
	//				}

	//				if (0 < b)
	//				{
	//					pixel_up = map_sketch.getPixel(a, b + 2 * map_height - 1);
	//				}

	//				if (a < map_sketch.getSize().x - 1)
	//				{
	//					pixel_right = map_sketch.getPixel(1 + a, b + 2 * map_height);
	//				}

	//				if (b < map_height - 1)
	//				{
	//					pixel_down = map_sketch.getPixel(a, 1 + b + 2 * map_height);
	//				}

	//				if (sf::Color(255, 255, 255) == pixel)
	//				{
	//					sprite_x = 8;

	//					if (sf::Color(255, 255, 255) == pixel_up)
	//					{
	//						sprite_y = 1;
	//					}

	//					if (sf::Color(255, 255, 255) == pixel_left)
	//					{
	//						if (sf::Color(255, 255, 255) != pixel_right)
	//						{
	//							sprite_x = 9;
	//						}
	//					}
	//					else if (sf::Color(255, 255, 255) == pixel_right)
	//					{
	//						sprite_x = 7;
	//					}
	//				}
	//				else if (sf::Color(146, 219, 0) == pixel)
	//				{
	//					sprite_x = 5;
	//				}
	//				else if (sf::Color(146, 146, 0) == pixel)
	//				{
	//					sprite_x = 4;
	//				}
	//				else if (sf::Color(146, 182, 0) == pixel)
	//				{
	//					sprite_x = 6;
	//				}
	//				else if (sf::Color(0, 73, 0) == pixel)
	//				{
	//					sprite_y = 1;

	//					if (sf::Color(0, 109, 0) == pixel_left)
	//					{
	//						if (sf::Color(0, 109, 0) != pixel_right)
	//						{
	//							sprite_x = 2;
	//						}
	//					}
	//					else if (sf::Color(0, 109, 0) == pixel_right)
	//					{
	//						sprite_x = 1;
	//					}
	//				}
	//				else if (sf::Color(0, 109, 0) == pixel)
	//				{
	//					sprite_y = 1;

	//					if (sf::Color(0, 73, 0) == pixel_left)
	//					{
	//						sprite_x = 3;
	//					}
	//					else if (sf::Color(0, 73, 0) == pixel_right)
	//					{
	//						sprite_x = 5;
	//					}
	//					else
	//					{
	//						sprite_x = 4;
	//					}
	//				}
	//				else if (sf::Color(109, 255, 85) == pixel)
	//				{
	//					sprite_x = 12;

	//					if (sf::Color(109, 255, 85) == pixel_up)
	//					{
	//						sprite_y = 1;
	//					}
	//				}

	//				cell_sprite.setTextureRect(sf::IntRect((CELL_SIZE / 4) * sprite_x, (CELL_SIZE / 4) * sprite_y, CELL_SIZE  / 4, CELL_SIZE / 4));

	//				cell_sprite.setScale(4.f, 4.f);

	//				i_window.draw(cell_sprite);
	//			}
	//		}
	//		else if (Cell::Empty != map[a][b])
	//		{
	//			if (Cell::Coin == map[a][b])
	//			{
	//				//coin_animation.set_position(CELL_SIZE * a, CELL_SIZE * b);
	//				//coin_animation.draw(i_window);
	//			}
	//			else if (Cell::QuestionBlock == map[a][b])
	//			{
	//				//question_block_animation.set_position(CELL_SIZE * a, CELL_SIZE * b);
	//				//question_block_animation.draw(i_window);
	//			}
	//			else
	//			{
	//				//Since the underground blocks have a different look, I placed their texture 2 cells below the regular ones in the map texture.
	//				sprite_y = 2 * i_underground;

	//				if (Cell::ActivatedQuestionBlock == map[a][b])
	//				{
	//					sprite_x = 6;
	//					sprite_y++;
	//				}
	//				else if (Cell::Pipe == map[a][b])
	//				{
	//					if (sf::Color(0, 182, 0) == map_sketch.getPixel(a, b))
	//					{
	//						sprite_y = 1;

	//						if (Cell::Pipe == map[a - 1][b])
	//						{
	//							sprite_x = 11;
	//						}
	//						else
	//						{
	//							sprite_x = 10;
	//						}
	//					}
	//					else if (sf::Color(0, 146, 0) == map_sketch.getPixel(a, b))
	//					{
	//						sprite_y = 0;

	//						if (sf::Color(0, 146, 0) == map_sketch.getPixel(a - 1, b))
	//						{
	//							sprite_x = 11;
	//						}
	//						else if (sf::Color(0, 146, 0) == map_sketch.getPixel(1 + a, b))
	//						{
	//							sprite_x = 10;
	//						}
	//						else
	//						{
	//							sprite_x = 10;

	//							if (sf::Color(0, 146, 0) == map_sketch.getPixel(a, b - 1))
	//							{
	//								sprite_y = 3;
	//							}
	//							else
	//							{
	//								sprite_y = 2;
	//							}
	//						}
	//					}
	//					else if (sf::Color(0, 219, 0) == map_sketch.getPixel(a, b))
	//					{
	//						if (sf::Color(0, 182, 0) == map_sketch.getPixel(1 + a, b))
	//						{
	//							sprite_x = 12;
	//						}
	//						else
	//						{
	//							sprite_x = 11;
	//						}

	//						if (sf::Color(0, 219, 0) == map_sketch.getPixel(a, b - 1))
	//						{
	//							sprite_y = 3;
	//						}
	//						else
	//						{
	//							sprite_y = 2;
	//						}
	//					}
	//				}
	//				else if (Cell::Wall == map[a][b])
	//				{
	//					if (sf::Color(0, 0, 0) == map_sketch.getPixel(a, b))
	//					{
	//						sprite_x = 2;
	//					}
	//					else
	//					{
	//						sprite_x = 3;
	//					}
	//				}

	//				cell_sprite.setTextureRect(sf::IntRect((CELL_SIZE / 4) * sprite_x, (CELL_SIZE / 4) * sprite_y, CELL_SIZE / 4, CELL_SIZE / 4));
	//				cell_sprite.setScale(4.f, 4.f);
	//				i_window.draw(cell_sprite);
	//			}
	//		}
	//	}
	//}

	////Drawing brick particles.
	//if (0 == i_draw_background)
	//{
	//	//for (const Object& brick_particle : brick_particles)
	//	//{
	//	//	//cerr << "!" << endl;
	//	//	cell_sprite.setPosition(brick_particle.x, brick_particle.y);
	//	//	cell_sprite.setTextureRect(sf::IntRect(0.25f * CELL_SIZE, CELL_SIZE * (0.25f + 2 * i_underground), 0.5f * CELL_SIZE, 0.5f * CELL_SIZE));
	//	//	i_window.draw(cell_sprite);
	//	//}
	//}
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
	//cerr << map_sketch.getSize().x * 64 << endl;
}


sf::Color LevelManager::get_map_sketch_pixel(const unsigned short i_x, const unsigned short i_y) const {
	/*if (i_x >= map_sketch.getSize().x || i_y >= map_sketch.getSize().y) {
		throw std::out_of_range("Pixel coordinates are out of bounds");
	}*/
	return map_sketch.getPixel(i_x, i_y);
}



void convert_sketch(const unsigned char i_current_level, unsigned short& i_level_finish, 
	vector<Enemy*>& i_enemies, vector<Block*> &Blocks, 
	sf::Color& i_background_color, LevelManager& i_level_manager, Mario& i_mario)
{
	unsigned short map_height;

	i_level_manager.update_map_sketch(i_current_level);
	//i_level_manager.set_map_size(i_level_manager.get_map_sketch_width());

	//We divide the height by 3 because the sketch stores the level as 3 layers: blocks, entities, and background tiles.
	map_height = floor(i_level_manager.get_map_sketch_height() / 3.f);

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
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "coin_block_1_1"));
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

