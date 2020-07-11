#include "../headers/NormalState.h"
#include "../headers/PlayerNet.h"

NormalState PlayerState::normal{};

NormalState::NormalState() {}

NormalState::~NormalState() {}

int NormalState::attack(PlayerNet& player, Entity* ent, int damage, bool canDodge) {
  if (player.getId() == ent->getId() && damage < 0){
    player.heal(-1 * damage);
    return 0;
  } 
  return ent->takeDamage(damage, canDodge);
}

