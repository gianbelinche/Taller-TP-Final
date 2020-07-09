#ifndef IMMOBILIZEDSTATE_H
#define IMMOBILIZEDSTATE_H

#include "PlayerState.h"

class ImmobilizedState : public PlayerState {
private:
  
public:
  ImmobilizedState();

  ~ImmobilizedState();

  void move(PlayerNet &player, int x, int y) override;

  void virtual update(PlayerNet &player);

  bool canMove() override;
};

#endif // IMMOBILIZEDSTATE_H
