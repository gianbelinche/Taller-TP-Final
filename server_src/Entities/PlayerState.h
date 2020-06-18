#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "../GameState.h"

class PlayerNet;
class GhostState;
class NormalState;
class MeditationState;

class PlayerState {
private:
  
public:
  PlayerState();

  ~PlayerState();

  void virtual update(PlayerNet &player);

  void virtual move(PlayerNet &player, int x, int y);

  void virtual lifeRecover(PlayerNet &player);

  void virtual manaRecover(PlayerNet &player);

public:
  static NormalState normal;
  static MeditationState meditating;
  static GhostState dead;
};
#endif // PLAYERSTATE_H
