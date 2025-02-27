#ifndef MONSTER_H
#define MONSTER_H

#include <vector>

#include "Entity.h"
#include "GameState.h"
#include "ServerEventListener.h"

class MonsterType;

class Monster : public Entity {
  friend class MonsterType;  // Para que pueda acceder al constructor
 private:
  MonsterType& kind;
  GameState& world;
  ServerEventListener& listener;
  int animFrame = 0;
  int velocity;
  int atkRange;
  int pursuitDistance;
  int attackCooldown;
  int currentAttackCooldown;
  int maxStepsToTake;
  int stepsToTake;
  int currentDirection;

  void moveToPlayer(PlayerNet* player);
 public:
  Monster(MonsterType& type, int id, int x, int y, int level, int velocity,
          int atkRange, int pursuitDistance, GameState& world,
          ServerEventListener& eventListener, int attackCooldown, int maxStepsPerdirection);

  ~Monster();

  // Pre: el jugador existe y esta vivo
  int attack(PlayerNet* player);

  bool canBeAttackedBy(Entity* ent) override;

  int getDeathExp(int attackerLevel) override;

  int getHitExp(int AttackerLevel, int damage) override;

  int takeDamage(int dmgToTake, bool canDodge) override;

  void update() override;

  void moveTo(int new_x, int new_y, int direction);

  std::vector<uint32_t> getSendable() override;

  int getNpcType();

  void moveRandom();

  bool mustBeDeleted() override;
};

#endif  // MONSTER_H
