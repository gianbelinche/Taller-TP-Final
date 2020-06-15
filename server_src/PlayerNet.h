#ifndef PLAYERNET_H
#define PLAYERNET_H

class GameState;

#include "PlayerState.h"

class PlayerNet {
private:
  int id; // Valor numerico que identifica al jugador en el cliente y el server
  PlayerState* state;
  int hp;
  int mana;
  int maxHp;
  int maxMana;
  int x;
  int y;
  int velocity;
  int level;
  int exp;
  int gold;
  GameState &world;
  int currFrame;
public:
  PlayerNet(int id, GameState &currState, int maxHP, int maxMana, int velocity,
            int currExp, int currGold);

  ~PlayerNet();

  void move(int x, int y);
};

#endif // PLAYERNET_H
