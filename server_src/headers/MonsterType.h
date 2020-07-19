#ifndef MONSTERTYPE_H
#define MONSTERTYPE_H

#include "ServerEventListener.h"
#include "Configuration.h"

class Monster;

class GameState;
class MonsterType {
 private:
  int hp;
  int damage;
  int level;
  int velocity;
  int atkRange;
  int pursuitDistance;
  int npcType;

 public:
  MonsterType(Configuration& config, std::string typeStr, int npcType);

  ~MonsterType();

  int getHp();

  int getDamage();

  int getNpcType();

  Monster* newMonster(int id, int x, int y, GameState& world,
                      ServerEventListener& eventListener);
};

#endif  // MONSTERTYPE_H
