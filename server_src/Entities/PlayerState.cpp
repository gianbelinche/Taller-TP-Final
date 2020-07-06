#include "../headers/PlayerState.h"

#include "../headers/Equations.h"
#include "../headers/PlayerNet.h"

#include <iostream>

PlayerState::PlayerState() {}

PlayerState::~PlayerState() {}

int PlayerState::attack(PlayerNet &player, Entity *ent, int damage) {
  return 0;
}

void PlayerState::lifeRecover(PlayerNet &player) {
  int healing = equation::pointsRecovery(
      player.getRaceRecovery(), player.getCurrFrame() / player.getFPS());
  player.heal(healing);
}

void PlayerState::move(PlayerNet &player, int x, int y) {
  player.setX(x);
  player.setY(y);
}

void PlayerState::update(PlayerNet &player) {
  lifeRecover(player);
  manaRecover(player); // Para el estado de meditacion cambia la recuperacion
}

void PlayerState::manaRecover(PlayerNet &player) {
  int manaGain = equation::pointsRecovery(
      player.getRaceRecovery(), player.getCurrFrame() / player.getFPS());

  player.recoverMana(manaGain);
}
