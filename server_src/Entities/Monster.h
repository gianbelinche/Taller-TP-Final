#ifndef MONSTER_H
#define MONSTER_H

#include "../GameState.h"
#include "Entity.h"

class MonsterType;

class Monster : public Entity {
  friend class MonsterType;  // Para que pueda acceder al constructor
 private:
  int hp;
  MonsterType &kind;
  GameState &world;

 public:
  Monster(MonsterType &type, int id, int x, int y, GameState &world);

  ~Monster();

  int takeDamage(int dmgToTake) override;

  void update() override;
};

#endif  // MONSTER_H
