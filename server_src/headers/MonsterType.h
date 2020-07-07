#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H

#include "ServerEventListener.h"

class Monster;

class GameState;
class MonsterType {
 private:
  int hp;
  int damage;
  int level;
  int npcType;
  int velocity;
  int atkRange;
  int pursuitDistance;

 public:
  MonsterType(int hp, int damage, int level, int npcType, int velocity,
              int atkRange, int pursuitDistance);

  ~MonsterType();

  int getHp();

  int getDamage();

  int getNpcType();

  Monster* newMonster(int id, int x, int y, GameState& world,
                      ServerEventListener& eventListener);
};

#endif  // MONSTERTYPE_H
