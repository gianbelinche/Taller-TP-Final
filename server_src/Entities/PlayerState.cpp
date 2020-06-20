#ifndef PLAYERSTATE_CPP
#define PLAYERSTATE_CPP

#include "../config/Equations.h"
#include "PlayerNet.h"
#include "PlayerState.h"

PlayerState::PlayerState() {}

PlayerState::~PlayerState() {}

void PlayerState::move(PlayerNet &player, int x, int y) {
  player.setX(x);
  player.setY(y);
}

#endif // PLAYERSTATE_CPP

void PlayerState::update(PlayerNet &player) {
  lifeRecover(player);
  manaRecover(player);
}

void PlayerState::lifeRecover(PlayerNet &player) {
  int healing = equation::pointsRecovery(player.getRaceRecovery(),
                                      player.getCurrFrame() / player.getFPS());
  player.heal(healing);
}

void PlayerState::manaRecover(PlayerNet &player) {
  int manaGain = equation::pointsRecovery(player.getRaceRecovery(),
                                       player.getCurrFrame() / player.getFPS());

  player.recoverMana(manaGain);
}

int PlayerState::attack(PlayerNet &player, Entity* ent, int damage) {}
