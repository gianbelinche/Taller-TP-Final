#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H

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

  Monster* newMonster(int x, int y);
};

#endif // MONSTERTYPE_H
