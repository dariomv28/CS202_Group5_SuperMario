#include "Headers/GameObject.h"

GameObject::GameObject(sf::Vector2f position, sf::Vector2f velocity, sf::Vector2f size) : position(position), velocity(velocity), size(size) {}

GameObject::GameObject(const GameObject& other) : position(other.position), velocity(other.velocity), size(other.size) {}

bool GameObject::checkCollision(const GameObject& other) {

}

sf::Vector2f GameObject::getPosition() {
	return position;
}