#include <iostream>
#include <vector>

#include "../headers/Entity.h"

Entity::Entity(int x, int y, int id, int maxHp, int level)
    : x(x),
      y(y), 
      id(id),
      hp(maxHp),
      maxHp(maxHp), 
      level(level),
      currentFrame(0) {
      }

Entity::~Entity() {}

void Entity::update() {}

int Entity::getId() {
  return id;
}

int Entity::getX() { return x; }

int Entity::getY() { return y; }

void Entity::setX(int new_x) { x = new_x; }

void Entity::setY(int new_y) { y = new_y; }

bool Entity::isAlive() { return hp > 0; }

int Entity::getHitExp(int AttackerLevel, int damage) {
  return 0;    
}

int Entity::getDeathExp(int attackerLevel) {
  return 0;
}

int Entity::getLevel() {
  return level;    
}

std::vector<uint32_t> Entity::getSendable() {
  return {};
}

bool Entity::mustBeDeleted() {
  return false;
}
