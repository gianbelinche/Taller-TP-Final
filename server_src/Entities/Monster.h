#ifndef MONSTER_H
#define MONSTER_H

#include "../GameState.h"
#include "Entity.h"

class MonsterType;

class Monster : public Entity {
  friend class MonsterType;  // Para que pueda acceder al constructor
 private:
  MonsterType &kind;
  GameState &world;

 public:
  Monster(MonsterType &type, int id, int x, int y, int level, GameState &world);

  ~Monster();

  // Pre: el jugador existe y esta vivo
  int attack(PlayerNet* player);

  int getDeathExp(int attackerLevel) override;

  int getHitExp(int AttackerLevel, int damage) override;

  int takeDamage(int dmgToTake) override;

  void update() override;
};

#endif  // MONSTER_H
