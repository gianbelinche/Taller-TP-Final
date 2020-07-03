#include "../headers/UserMoved.h"

UserMoved::UserMoved(int originUser, char direction)
    : Event(originUser), direction(direction) {}

UserMoved::~UserMoved() {}

char UserMoved::getDirection() { return direction; }

UserMoved::UserMoved(UserMoved&& other)
    : Event(other.originUserId), direction(other.direction) {}

UserMoved& UserMoved::operator=(UserMoved&& other) {
  this->originUserId = other.originUserId;
  this->direction = other.direction;
  return *this;
}
