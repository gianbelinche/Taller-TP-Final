

#include "Entity.h"

Entity::Entity(int x, int y, int id) : x(x), y(y), id(id) {}

Entity::~Entity() {}

void Entity::update() {}

int Entity::getX() {
  return x;    
}

int Entity::getY() {
  return y;    
}
