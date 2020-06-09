#include "PlayerTestNet.h"

PlayerTestNet::PlayerTestNet(int id) : x(0), y(0), id(id) {}

PlayerTestNet::~PlayerTestNet() {}

const int PlayerTestNet::getX() {
  return x;
}

const int PlayerTestNet::getY() {
  return y;
}

void PlayerTestNet::setX(int new_x) {
  x = new_x;
}

void PlayerTestNet::setY(int new_y) {
  y = new_y;
}
