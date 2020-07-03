#include "../headers/NormalState.h"

NormalState PlayerState::normal{};

NormalState::NormalState() {}

NormalState::~NormalState() {}

int NormalState::attack(PlayerNet& player, Entity* ent, int damage) {
  return ent->takeDamage(damage);
}
