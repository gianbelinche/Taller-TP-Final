

#include "PlayerState.h"
#include "PlayerNet.h"
#include "NormalState.h"

class MeditationState : public PlayerState {
private:
  
public:
  MeditationState();

  ~MeditationState();

  void move(PlayerNet &player, int x, int y) override;

  void manaRecover(PlayerNet &player) override;
};
