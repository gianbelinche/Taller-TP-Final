

#include "Entity.h"

Entity::Entity(int x, int y, int id) : x(x), y(y), id(id), currentFrame(0) {}

Entity::~Entity() {}

void Entity::update() {}

int Entity::getX() {
  return x;    
}

int Entity::getY() {
  return y;    
}

void Entity::setX(int new_x) {
  x = new_x;        
}

void Entity::setY(int new_y) {
  y = new_y;    
}
