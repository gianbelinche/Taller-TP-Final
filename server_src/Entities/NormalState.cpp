#include "NormalState.h"

NormalState::NormalState() {}

NormalState::~NormalState() {}

int NormalState::attack(PlayerNet& player, Entity* ent, int damage) {
  return ent->takeDamage(damage);
}
