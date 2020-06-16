#ifndef MONSTER_H
#define MONSTER_H

#include "Entity.h"

class MonsterType;

class Monster : public Entity {
  friend class MonsterType; // Para que pueda acceder al constructor
private:
  int hp;
  MonsterType &kind;
public:
  Monster(MonsterType &type, int x, int y);

  ~Monster();

  void update() override;
};

#endif // MONSTER_H
