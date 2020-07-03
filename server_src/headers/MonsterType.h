#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H

#include "GameState.h"
#include "Monster.h"

class MonsterType {
 private:
  int hp;
  int damage;

 public:
  MonsterType(int hp, int damage);

  ~MonsterType();

  int getHp();

  int getDamage();

  Monster* newMonster(int id, int x, int y, int level, GameState& world);
};

#endif  // MONSTERTYPE_H
