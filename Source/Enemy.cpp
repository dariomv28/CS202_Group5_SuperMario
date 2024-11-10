#include "Headers/Enemy.h"

Enemy::Enemy(std::string type, bool isDefeated): type(type), isDefeated(isDefeated) {}

Enemy::Enemy(const Enemy& other) : type(other.type), isDefeated(isDefeated) {}

void Enemy::move() {

}

void Enemy::attack() {

}

void Enemy::takeDamage() {

}

void Enemy::respawn() {

}

void Enemy::update() {

}

