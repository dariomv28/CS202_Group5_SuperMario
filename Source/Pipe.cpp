#include "Headers/Pipe.h"

Pipe::Pipe() : Block() {
}

Pipe::Pipe(sf::Vector2f position, sf::Vector2f size, std::string name, int height)
	: Block(position, size, name)
{
	int sizeY = size.y / height;
	int sizeX = size.x / 2;
	sprite_pipe.resize(2*height);

	//Bottom of the pipe
	for (int i = 0; i < height-1; i++) {
		//Left side of the pipe
		sprite_pipe[2*i].setTexture(entityTexture);
		sprite_pipe[2*i].setTextureRect(spritesSheet["pipe_bottom_left"]);
		sprite_pipe[2*i].setScale(size.x / sprite_pipe[i].getGlobalBounds().width, sizeY / sprite_pipe[i].getGlobalBounds().height);
		sprite_pipe[2*i].setPosition(sf::Vector2f(position.x, position.y + i*sizeY));

		//Right side of the pipe
		sprite_pipe[2*i+1].setTexture(entityTexture);
		sprite_pipe[2*i+1].setTextureRect(spritesSheet["pipe_bottom_right"]);
		sprite_pipe[2*i+1].setScale(size.x / sprite_pipe[i].getGlobalBounds().width, sizeY / sprite_pipe[i].getGlobalBounds().height);
		sprite_pipe[2*i+1].setPosition(sf::Vector2f(position.x + sizeX, position.y + i*sizeY));
	}

	//Top of the pipe
	sprite_pipe[2*height-2].setTexture(entityTexture);
	sprite_pipe[2*height-2].setTextureRect(spritesSheet["pipe_top_left"]);
	sprite_pipe[2*height-2].setScale(size.x / sprite_pipe[2*height-2].getGlobalBounds().width, sizeY / sprite_pipe[2*height-2].getGlobalBounds().height);
	sprite_pipe[2*height-2].setPosition(sf::Vector2f(position.x, position.y + (height-1)*sizeY));

	sprite_pipe[2*height-1].setTexture(entityTexture);
	sprite_pipe[2*height-1].setTextureRect(spritesSheet["pipe_top_right"]);
	sprite_pipe[2*height-1].setScale(size.x / sprite_pipe[2*height-1].getGlobalBounds().width, sizeY / sprite_pipe[2*height-1].getGlobalBounds().height);
	sprite_pipe[2*height-1].setPosition(sf::Vector2f(position.x + sizeX, position.y + (height-1)*sizeY));
}

Pipe::~Pipe() {
}

void Pipe::update(const float& dt) {

}

void Pipe::reactToCollison(int collidedSide) {

}

void Pipe::render(sf::RenderTarget* target) {
	for (auto& pipe : sprite_pipe) {
		target->draw(pipe);
	}
	target->draw(hitbox);
}
