#ifndef NORMALSTATE_H
#define NORMALSTATE_H

#include "PlayerState.h"

class NormalState : public PlayerState {
 private:
 public:
  NormalState();

  ~NormalState();

  int attack(PlayerNet& player, Entity* ent, int damage, bool canDodge) override;
};

#endif  // NORMALSTATE_H
