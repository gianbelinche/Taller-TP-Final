#include <iostream>

#include "../headers/Entity.h"

Entity::Entity(int x, int y, int id, int maxHp, int hp, int level)
    : x(x),
      y(y), 
      id(id),
      hp(hp),
      maxHp(maxHp), 
      level(level),
      currentFrame(0) {
  std::cout << "Se creo con: " << maxHp << " de vida\n";
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
