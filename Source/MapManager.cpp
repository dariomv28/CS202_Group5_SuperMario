#include "Headers/MapManager.h"

MapManager::MapManager(sf::RenderWindow* window) {
	CurrentLeft = 0;
	CurrentRight = SCREEN_WIDTH;
	this->window = window;
	view_x = 0;
	View = sf::View(sf::FloatRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT));
	initStyle();
}

MapManager::~MapManager() {
    
}

void MapManager::initStyle() {
	//General styles
	styles[1] = "basic";
	styles[2] = "snow";
	styles[3] = "gray";
	// /Pipe styles
	pipe_styles[1] = "basic";
	pipe_styles[2] = "basic";
	pipe_styles[3] = "gray";
}

void MapManager::update(PlayerManager* player, float dt) {
	updateView(player);
  
}


void MapManager::updateView(PlayerManager* Player) {
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

unsigned short MapManager::get_map_sketch_height() const
{
	return map_sketch.getSize().y;
}

unsigned short MapManager::get_map_sketch_width() const
{
	return map_sketch.getSize().x;
}

void MapManager::draw_map(sf::RenderTarget* target)
{
	if (!target)
		target = window;
	target->draw(backgroundSprite);
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

void MapManager::get_map_sketch(const unsigned int i_current_level)
{
	map_sketch.loadFromFile("Source/Resources/texture/LevelSketch" + std::to_string(i_current_level) + ".png");
	return;
}

void MapManager::update_background(const unsigned int i_current_level)
{
	std::string current_level = std::to_string(i_current_level);
	backgroundTexture.loadFromFile("Source/Resources/texture/" + styles[i_current_level] + "_background.png");
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setScale(float((get_map_sketch_width() * 64 * 1.0) / backgroundSprite.getTexture()->getSize().x * 1.0), (get_map_sketch_height() * 64 / 3.f) / backgroundSprite.getTexture()->getSize().y);
	backgroundSprite.setPosition(0, 0);
}


sf::Color MapManager::get_map_sketch_pixel(const unsigned short i_x, const unsigned short i_y) const {
	if (i_x >= map_sketch.getSize().x || i_y >= map_sketch.getSize().y) {
		throw std::out_of_range("Pixel coordinates are out of bounds");
	}
	return map_sketch.getPixel(i_x, i_y);
}



void MapManager::convert_sketch(const unsigned int i_current_level, vector<Enemy*>& i_enemies, 
	vector<Block*> &Blocks, vector<PowerUpObject*>& PowerUp , PlayerManager* i_mario)
{
	get_map_sketch(i_current_level);
	update_background(i_current_level);

	int map_width = get_map_sketch_width();
	int map_height = floor(get_map_sketch_height() / 3.f);

	// get map_sketch's begining point on x-axis
	//unsigned short x = i_level_manager.get_map_sketch_width() - 1;
	//i_background_color = i_level_manager.get_map_sketch_pixel(0, i_level_manager.get_map_sketch_height() - 1);

	for (unsigned short a = 0; a < map_width; a++)
	{
		for (unsigned short b = 0; b < 2 * map_height; b++)
		{
			sf::Color pixel = get_map_sketch_pixel(a, b);

			if (b < map_height)
			{
				//Ground
				if (pixel == sf::Color(255, 200, 200))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						styles[i_current_level] + "_underground_mid"));
				else if (pixel == sf::Color(220, 220, 220))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						styles[i_current_level] + "_ground_mid"));
				else if (pixel == sf::Color(240, 240, 240))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						styles[i_current_level] + "_ground_left"));
				else if (pixel == sf::Color(255, 225, 225))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						styles[i_current_level] + "_underground_left"));
				else if (pixel == sf::Color(200, 200, 200))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						styles[i_current_level] + "_ground_right"));
				else if (pixel == sf::Color(255, 175, 175))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						styles[i_current_level] + "_underground_right"));
				else if (pixel == sf::Color(117, 117, 117))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						"gray_block1"));
				else if (pixel == sf::Color(89, 89, 89))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE),
						"gray_block2"));
				//Special blocks
				else if (pixel == sf::Color(193, 113, 52))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), styles[i_current_level] + "_wall"));
				else if (pixel == sf::Color(146, 73, 0))
					Blocks.push_back(new Brick(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), styles[i_current_level] + "_brick", false));
				else if (pixel == sf::Color(81, 34, 19))
					Blocks.push_back(new Brick(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), styles[i_current_level] + "_brick", true));
				else if (pixel == sf::Color(255, 146, 85))
					Blocks.push_back(new CoinBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "coin_block"));
				else if (pixel == sf::Color(246, 109, 109))
					Blocks.push_back(new MushroomBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "mushroom_block", 1));
				else if (pixel == sf::Color(146, 73, 100))
					Blocks.push_back(new MushroomBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "mushroom_block", 2));
				else if (pixel == sf::Color(146, 73, 150))
					Blocks.push_back(new MushroomBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "mushroom_block", 3));
				else if (pixel.r == 0 && pixel.b == 0 && pixel.g >= 250)
					Blocks.push_back(new Pipe(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE * 2, CELL_SIZE * (255 - pixel.g)),
						pipe_styles[i_current_level] + "_pipe", 255 - pixel.g));
				else if (pixel == sf::Color(255, 77, 0))
					PowerUp.push_back(new Lava(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "lava"));
				else if (pixel == sf::Color(175, 55, 0))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "lava_bottom"));
				else if (pixel == sf::Color(198, 60, 60))
					Blocks.push_back(new Trampoline(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "trampoline"));
				else if (pixel == sf::Color(67, 67, 67))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "cannon_mid"));
				else if (pixel == sf::Color(102, 102, 102))
					Blocks.push_back(new SolidBlock(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "cannon_bottom"));
				else if (pixel == sf::Color(0,0,0))
					Blocks.push_back(new Cannon(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "cannon"));
				//Power Ups
				else if (pixel == sf::Color(255, 177, 13)) {
					PowerUp.push_back(new Coin(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * b), sf::Vector2f(CELL_SIZE, CELL_SIZE), "coin"));
				}
			}
			else
			{
				if (sf::Color(255, 0, 0) == pixel)
				{
					i_mario->setPosition(CELL_SIZE * a, 250);
				}
				else if (sf::Color(155, 0, 0) == pixel)
				{
					i_enemies.push_back(new Goomba(sf::Vector2f(CELL_SIZE*a, CELL_SIZE * (b- map_height)), sf::Vector2f(CELL_SIZE, CELL_SIZE)));
				}
				else if (sf::Color(0, 125, 0) == pixel)
				{
					i_enemies.push_back(new Koopa(sf::Vector2f(CELL_SIZE * a, CELL_SIZE * (b - map_height)), sf::Vector2f(CELL_SIZE, CELL_SIZE)));
				}
			}
		}
	}
}

