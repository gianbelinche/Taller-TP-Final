#ifndef PLAYERSTATE_H
#define PLAYERSTATE_H

#include "Entity.h"

class PlayerNet;
class GhostState;
class NormalState;
class MeditationState;
class ImmobilizedState;

class PlayerState {
 private:
 public:
  PlayerState();

  virtual ~PlayerState();

  virtual bool canMove();

  void virtual update(PlayerNet &player);

  void virtual move(PlayerNet &player, int x, int y);

  int virtual attack(PlayerNet &player, Entity *ent, int damage);

  void virtual lifeRecover(PlayerNet &player);

  void virtual manaRecover(PlayerNet &player);

 public:
  static NormalState normal;
  static MeditationState meditating;
  static GhostState dead;
  static ImmobilizedState immobilized;
};
#endif  // PLAYERSTATE_H
