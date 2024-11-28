#include "Headers/GameObject.h"

GameObject::GameObject() {};

GameObject::GameObject(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicsEngine) : 
		position(position), size(size), physicsEngine(physicsEngine) {
	/*hitbox.setSize(size);
	hitbox.setPosition(position);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.f);*/
}

sf::Vector2f GameObject::getPosition() {
	return position;
}

sf::Vector2f GameObject::getSize() {
	return size;
}

sf::Vector2f GameObject::getCenter() const {
	return hitbox.getPosition() + sf::Vector2f(hitbox.getSize().x / 2, hitbox.getSize().y / 2);
}

void GameObject::setPosition(const sf::Vector2f& pos) {
    position = pos;
    entitySprite.setPosition(pos);
    hitbox.setPosition(pos);
}

void GameObject::setSize(const sf::Vector2f& newSize) {
    size = newSize;
    // Update hitbox size
    hitbox.setSize(size);
}

void GameObject::setPosition(float x, float y) {
	position = sf::Vector2f(x, y);
	entitySprite.setPosition(position);
	// Make sure hitbox follows the position exactly
	hitbox.setPosition(position);
}