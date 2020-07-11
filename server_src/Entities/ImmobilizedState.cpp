#include "../headers/ImmobilizedState.h"
#include "../headers/PlayerNet.h"

ImmobilizedState PlayerState::immobilized{};

ImmobilizedState::ImmobilizedState() {}

ImmobilizedState::~ImmobilizedState() {}

void ImmobilizedState::update(PlayerNet &player) {
  player.decreaseImmobilizedFramesLeft();
}

void ImmobilizedState::move(PlayerNet &player, int x, int y) {}

bool ImmobilizedState::canMove() {
  return false;
}

bool ImmobilizedState::isAlive() {
  return false;
}

