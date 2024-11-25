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
    sf::FloatRect thisBounds = this->hitbox.getGlobalBounds();
    sf::FloatRect objectBounds = obj->hitbox.getGlobalBounds();
	float thisLeft = thisBounds.left;
	float thisRight = thisBounds.left + thisBounds.width;
	float thisTop = thisBounds.top;
	float thisBottom = thisBounds.top + thisBounds.height;

	float objectLeft = objectBounds.left;
	float objectRight = objectBounds.left + objectBounds.width;
	float objectTop = objectBounds.top;
	float objectBottom = objectBounds.top + objectBounds.height;

    if (thisBounds.intersects(objectBounds)) {
		// Determine which side the collision occurred
		float overlapLeft = thisRight - objectLeft;
		float overlapRight = objectRight - thisLeft;
		float overlapTop = thisBottom - objectTop;
		float overlapBottom = objectBottom - thisTop;

		// The side with the smallest overlap is where the collision happened
		return (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight);
    }
    return false;
}

bool GameObject::checkCollisionDown(GameObject* obj) {
    sf::FloatRect thisBounds = this->hitbox.getGlobalBounds();
    sf::FloatRect objectBounds = obj->hitbox.getGlobalBounds();
	float thisLeft = thisBounds.left -10;
	float thisRight = thisBounds.left + thisBounds.width+10;
	float thisTop = thisBounds.top-10;
	float thisBottom = thisBounds.top + thisBounds.height+10;

	float objectLeft = objectBounds.left;
	float objectRight = objectBounds.left + objectBounds.width;
	float objectTop = objectBounds.top;
	float objectBottom = objectBounds.top + objectBounds.height;

    if (thisBounds.intersects(objectBounds)) {
		// Determine which side the collision occurred
		float overlapLeft = thisRight - objectLeft;
		float overlapRight = objectRight - thisLeft;
		float overlapTop = thisBottom - objectTop;
		float overlapBottom = objectBottom - thisTop;

		// The side with the smallest overlap is where the collision happened
		return (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight);
    }
    return false;
}

bool GameObject::checkCollisionLeft(GameObject* obj) {
    sf::FloatRect thisBounds = this->hitbox.getGlobalBounds();
    sf::FloatRect objectBounds = obj->hitbox.getGlobalBounds();
	float thisLeft = thisBounds.left;
	float thisRight = thisBounds.left + thisBounds.width;
	float thisTop = thisBounds.top;
	float thisBottom = thisBounds.top + thisBounds.height;

	float objectLeft = objectBounds.left;
	float objectRight = objectBounds.left + objectBounds.width;
	float objectTop = objectBounds.top;
	float objectBottom = objectBounds.top + objectBounds.height;

    if (thisBounds.intersects(objectBounds)) {
		// Determine which side the collision occurred
		float overlapLeft = thisRight - objectLeft;
		float overlapRight = objectRight - thisLeft;
		float overlapTop = thisBottom - objectTop;
		float overlapBottom = objectBottom - thisTop;

		// The side with the smallest overlap is where the collision happened
		return (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom);
    }
    return false;
}

bool GameObject::checkCollisionRight(GameObject* obj) {
    sf::FloatRect thisBounds = this->hitbox.getGlobalBounds();
    sf::FloatRect objectBounds = obj->hitbox.getGlobalBounds();
	float thisLeft = thisBounds.left;
	float thisRight = thisBounds.left + thisBounds.width;
	float thisTop = thisBounds.top;
	float thisBottom = thisBounds.top + thisBounds.height;

	float objectLeft = objectBounds.left;
	float objectRight = objectBounds.left + objectBounds.width;
	float objectTop = objectBounds.top;
	float objectBottom = objectBounds.top + objectBounds.height;

    if (thisBounds.intersects(objectBounds)) {
		// Determine which side the collision occurred
		float overlapLeft = thisRight - objectLeft;
		float overlapRight = objectRight - thisLeft;
		float overlapTop = thisBottom - objectTop;
		float overlapBottom = objectBottom - thisTop;

		// The side with the smallest overlap is where the collision happened
		return (overlapRight < overlapLeft && overlapRight < overlapTop && overlapRight < overlapBottom);
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