#ifndef PLAYERNET_H
#define PLAYERNET_H

class GameState;

#include "Class.h"
#include "Entity.h"
#include "Race.h"
#include "PlayerState.h"

class PlayerNet : public Entity{
private:
  PlayerState* state;
  Class playerClass;
  Race playerRace;
  int hp;
  int mana;
  int maxHp;
  int maxMana;
  int velocity;
  int level;
  int exp;
  int gold;
  GameState &world;
public:
  PlayerNet(int x, int y, int id, GameState &currState, int maxHP, int maxMana,
            int velocity, int currExp, int currGold);

  ~PlayerNet();

  void move(int x, int y);
};

#endif // PLAYERNET_H
