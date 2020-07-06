#include "PlayerState.h"

class ImmobilizedState : public PlayerState {
private:
  
public:
  ImmobilizedState();

  ~ImmobilizedState();

  void move(PlayerNet &player, int x, int y) override;

  void virtual update(PlayerNet &player);
};
