#include "../headers/ImmobilizedState.h"

ImmobilizedState PlayerState::immobilized{};

ImmobilizedState::ImmobilizedState() {}

ImmobilizedState::~ImmobilizedState() {}

void ImmobilizedState::update(PlayerNet &player) {
  // Logica de esperar x tiempo sin hacer nada
}

void ImmobilizedState::move(PlayerNet &player, int x, int y) {}
