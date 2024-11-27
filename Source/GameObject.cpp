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

bool GameObject::checkCollisionUp(GameObject* obj) {
	//// get top left and bottom right corners of the obj
	//sf::Vector2f objTopLeft = obj->hitbox.getPosition();
	//sf::Vector2f objBottomRight = obj->hitbox.getPosition() + obj->hitbox.getSize();
	//// get top left and bottom right corners of this object
	//sf::Vector2f thisTopLeft = hitbox.getPosition() + sf::Vector2f(0,-1);
	//sf::Vector2f thisBottomRight = hitbox.getPosition() + hitbox.getSize();

	//// check if the two rectangles intersect
	//if (thisTopLeft.x <= objBottomRight.x && thisBottomRight.x >= objTopLeft.x &&
	//	thisTopLeft.y <= objBottomRight.y && thisBottomRight.y >= objTopLeft.y) {
	//	return true;
	//}
	//return false;
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		float dyTop = intersection.top + intersection.height - hitbox.getGlobalBounds().top;
		return dyTop > 0 && dyTop < hitbox.getGlobalBounds().height;
	}
	return false;
}

bool GameObject::checkCollisionDown(GameObject* obj) {
	// get top left and bottom right corners of the obj
	//sf::Vector2f objTopLeft = obj->hitbox.getPosition();
	//sf::Vector2f objBottomRight = obj->hitbox.getPosition() + obj->hitbox.getSize();
	//// get top left and bottom right corners of this object
	//sf::Vector2f thisTopLeft = hitbox.getPosition();
	//sf::Vector2f thisBottomRight = hitbox.getPosition() + hitbox.getSize() + sf::Vector2f(0, 1);

	//// check if the two rectangles intersect
	//if (thisTopLeft.x <= objBottomRight.x && thisBottomRight.x >= objTopLeft.x &&
	//	thisTopLeft.y <= objBottomRight.y && thisBottomRight.y >= objTopLeft.y) {
	//	return true;
	//}
	//return false;
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		// The bottom of the intersection box should be below the top of the first object
		return intersection.top + intersection.height > hitbox.getGlobalBounds().top;
	}
	return false;
}

bool GameObject::checkCollisionLeft(GameObject* obj) {
	// get top left and bottom right corners of the obj
	//sf::Vector2f objTopLeft = obj->hitbox.getPosition();
	//sf::Vector2f objBottomRight = obj->hitbox.getPosition() + obj->hitbox.getSize();
	//// get top left and bottom right corners of this object
	//sf::Vector2f thisTopLeft = hitbox.getPosition() + sf::Vector2f(-1, 0);
	//sf::Vector2f thisBottomRight = hitbox.getPosition() + hitbox.getSize();

	//// check if the two rectangles intersect
	//if (thisTopLeft.x <= objBottomRight.x && thisBottomRight.x >= objTopLeft.x &&
	//	thisTopLeft.y <= objBottomRight.y && thisBottomRight.y >= objTopLeft.y) {
	//	std::cerr << "__________________________________" << "\n";
	//	std::cerr << sf::Vector2f(thisTopLeft.x, thisTopLeft.y).x << " " << sf::Vector2f(thisTopLeft.x, thisTopLeft.y).y << "\n";
	//	std::cerr << sf::Vector2f(thisBottomRight.x, thisBottomRight.y).x << " " << sf::Vector2f(thisBottomRight.x, thisBottomRight.y).y << "\n";
	//	std::cerr << "space\n";
	//	std::cerr << sf::Vector2f(objTopLeft.x, objTopLeft.y).x << " " << sf::Vector2f(objTopLeft.x, objTopLeft.y).y << "\n";
	//	std::cerr << sf::Vector2f(objBottomRight.x, objBottomRight.y).x << " " << sf::Vector2f(objBottomRight.x, objBottomRight.y).y << "\n";
	//	return true;
	//}
	//return false;
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		float dxLeft = intersection.left + intersection.width - hitbox.getGlobalBounds().left;
		return dxLeft > 0 && dxLeft < hitbox.getGlobalBounds().width;
	}
	return false;
}

bool GameObject::checkCollisionRight(GameObject* obj) {
	// get top left and bottom right corners of the obj
	//sf::Vector2f objTopLeft = obj->hitbox.getPosition();
	//sf::Vector2f objBottomRight = obj->hitbox.getPosition() + obj->hitbox.getSize();
	//// get top left and bottom right corners of this object
	//sf::Vector2f thisTopLeft = hitbox.getPosition();
	//sf::Vector2f thisBottomRight = hitbox.getPosition() + hitbox.getSize() + sf::Vector2f(1, 0);

	//// check if the two rectangles intersect
	//if (thisTopLeft.x <= objBottomRight.x && thisBottomRight.x >= objTopLeft.x &&
	//	thisTopLeft.y <= objBottomRight.y && thisBottomRight.y >= objTopLeft.y) {
	//	return true;
	//}
	//return false;
	sf::FloatRect intersection;
	if (hitbox.getGlobalBounds().intersects(obj->hitbox.getGlobalBounds(), intersection)) {
		float dxRight = obj->hitbox.getGlobalBounds().left - (hitbox.getGlobalBounds().left + hitbox.getGlobalBounds().width);
		return dxRight > 0 && dxRight < obj->hitbox.getGlobalBounds().width;
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