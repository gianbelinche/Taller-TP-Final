#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H

#include "GameState.h"
#include "Monster.h"
#include "ServerEventListener.h"

class MonsterType {
 private:
  int hp;
  int damage;
  int level;
 public:
  MonsterType(int hp, int damage, int level);

  ~MonsterType();

  int getHp();

  int getDamage();

  Monster* newMonster(int id, int x, int y, GameState& world,
                      ServerEventListener& eventListener);
};

#endif  // MONSTERTYPE_H
