

#include "PlayerNet.h"
#include "PlayerState.h"

PlayerNet::PlayerNet(int x, int y, int id, GameState &currState, int maxHP,
                     int maxMana, int velocity, int currExp, int currGold) :
                     Entity(x, y, id), world(currState), maxHp(maxHP),
                     maxMana(maxMana), velocity(velocity), exp(currExp),
                     gold(currGold) {}

PlayerNet::~PlayerNet() {}

void PlayerNet::move(int x, int y) {
  state->move(*this, x, y);
}