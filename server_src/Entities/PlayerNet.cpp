

#include "PlayerNet.h"
#include "PlayerState.h"

PlayerNet::PlayerNet(int x, int y, int id, GameState &currState, int hp,
                     int mana, int velocity, int currExp, int currGold) :
                     Entity(x, y, id), hp(hp), mana(mana), world(currState),
                     velocity(velocity), exp(currExp), gold(currGold) {}

PlayerNet::~PlayerNet() {}

void PlayerNet::move(int x, int y) {
  state->move(*this, x, y);
}
void PlayerNet::PlayerNet::changeState(PlayerState* new_state) {
  state = new_state;
}
