

#include "UserMoved.h"

UserMoved::UserMoved(int originUser, int pos_x, int pos_y) : 
            Event(originUser), x(pos_x), y(pos_y) {}

UserMoved::~UserMoved() {}

int UserMoved::getX() {
  return x;
}

int UserMoved::getY() {
  return y;
}