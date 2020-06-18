#ifndef PLAYERNET_H
#define PLAYERNET_H

class GameState;

#include "Class.h"
#include "Entity.h"
#include "Race.h"
#include "PlayerState.h"

class PlayerNet : public Entity{
private:
  PlayerState* state; // Ver si puede ser una referencia
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
  PlayerNet(int x, int y, int id, GameState &currState, int hp, int mana,
            int velocity, int currExp, int currGold);

  ~PlayerNet();

  // Pre: la posicion es valida(no colisiona)
  void move(int x, int y);

  void changeState(PlayerState* new_state);
};

#endif // PLAYERNET_H
