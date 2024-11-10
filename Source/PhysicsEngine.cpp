#include "Headers/PhysicsEngine.h"

void PhysicsEngine::applyGravity(GameObject& obj) {
	obj.setForce(gravity);
}

