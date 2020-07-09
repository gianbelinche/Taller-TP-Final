#ifndef GHOSTSTATE_H
#define GHOSTSTATE_H

#include "PlayerNet.h"
#include "PlayerState.h"

class GhostState : public PlayerState {
 private:
 public:
  GhostState();

  ~GhostState();

  void update(PlayerNet &player) override;

  bool isAlive() override;
};
#endif  // GHOSTSTATE_H
