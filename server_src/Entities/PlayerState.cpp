#ifndef PLAYERSTATE_CPP
#define PLAYERSTATE_CPP

#include "PlayerNet.h"
#include "PlayerState.h"

PlayerState::PlayerState() {}

PlayerState::~PlayerState() {}

void PlayerState::move(PlayerNet &player, int x, int y) {
  player.setX(x);
  player.setY(y);
}

#endif // PLAYERSTATE_CPP

void PlayerState::update() {}
