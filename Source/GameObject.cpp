#include "Headers/GameObject.h"

GameObject::GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f size) : position(position), velocity(velocity), size(size) {}

GameObject::GameObject(const GameObject& other) : position(other.position), velocity(other.velocity), size(other.size) {}

bool GameObject::checkCollision(const GameObject& other) {
	if ((other.position.y == position.y - other.size.y || other.position.y == position.y + size.y) && other.position.x >= position.x - other.size.x && other.position.x <= position.x + other.size.x) {
		return true;
	}
	else if ((other.position.x == position.x - other.size.x || other.position.x == position.x + size.x) && other.position.y >= position.y - other.size.y && other.position.y <= position.y + other.size.y) {
		return true;
	}
	return false;
}

sf::Vector2f GameObject::getPosition() {
	return position;
}