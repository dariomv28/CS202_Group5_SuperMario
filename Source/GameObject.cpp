#include "Headers/GameObject.h"

GameObject::GameObject() {};

GameObject::GameObject(sf::Vector2f position, sf::Vector2f size, PhysicsEngine* physicsEngine) : 
		position(position), size(size), physicsEngine(physicsEngine) {
	hitbox.setSize(size);
	hitbox.setPosition(position);
	hitbox.setFillColor(sf::Color::Transparent);
	hitbox.setOutlineColor(sf::Color::Red);
	hitbox.setOutlineThickness(1.f);
}

sf::Vector2f GameObject::getPosition() {
	return position;
}

sf::Vector2f GameObject::getSize() {
	return size;
}

bool GameObject::checkCollisionUp(GameObject* obj) {
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		float dyTop = intersection.top - hitbox.getGlobalBounds().top;
		return dyTop > 0 && dyTop <= hitbox.getGlobalBounds().height;
	}
	return false;
}

bool GameObject::checkCollisionDown(GameObject* obj) {
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		float dyBottom = (hitbox.getGlobalBounds().top + hitbox.getGlobalBounds().height) -
			(intersection.top + intersection.height);
		return dyBottom >= 0 && dyBottom < hitbox.getGlobalBounds().height;
	}
	return false;
}

bool GameObject::checkCollisionLeft(GameObject* obj) {
	if (checkCollisionDown(obj)) {
		return false;
	}
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		float dxLeft = intersection.left - hitbox.getGlobalBounds().left;
		return dxLeft > 0 && dxLeft <= hitbox.getGlobalBounds().width;
	}
	return false;
}

bool GameObject::checkCollisionRight(GameObject* obj) {
	if (checkCollisionDown(obj)) {
		return false;
	}
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		float dxRight = (hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width) -
			(intersection.left + intersection.width);
		return dxRight > 0 && dxRight <= hitbox.getGlobalBounds().width;
	}
	return false;
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