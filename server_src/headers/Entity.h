#ifndef ENTITY_H
#define ENTITY_H

#include <vector>
#include <cstdint>

#define NPC_TYPE 0
#define MOB_TYPE 1
#define PLAYER_TYPE 2

class Entity {
 protected:

  int x;
  int y;
  int id;  // Valor numerico que identifica a la entida en el cliente y el
           // server
  int hp;
  int maxHp;
  int level;
  int currentFrame;

 public:
  Entity(int x, int y, int id, int maxHp, int level);

  ~Entity();

  int virtual getHitExp(int AttackerLevel, int damage);

  int virtual getDeathExp(int attackerLevel);

  int getId();

  int getLevel();

  int getX();

  int getY();

  void setX(int new_x);

  void setY(int new_y);

  virtual void update();

  bool isAlive();

  bool virtual canBeAttackedBy(Entity* ent) = 0;

  int virtual takeDamage(int dmgToTake) = 0;

  std::vector<uint32_t> virtual getSendable();
};

#endif  // ENTITY_H
