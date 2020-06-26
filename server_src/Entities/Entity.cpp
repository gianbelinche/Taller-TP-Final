

#include "Entity.h"

Entity::Entity(int x, int y, int id, int hp)
    : x(x), y(y), id(id), currentFrame(0), hp(hp) {}

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
