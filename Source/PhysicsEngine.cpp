#include "Headers/PhysicsEngine.h"

void PhysicsEngine::applyGravity(GameObject& obj) {
	obj.setForce(gravity);
}
bool PhysicsEngine::checkCollision(GameObject& obj1, GameObject& obj2) {
	return obj1.checkCollision(obj2);
}
void PhysicsEngine::resolveCollision(GameObject& obj1, GameObject& obj2) {

}