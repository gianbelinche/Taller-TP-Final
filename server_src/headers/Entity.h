#ifndef ENTITY_H
#define ENTITY_H

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
  Entity(int x, int y, int id, int maxHp, int hp, int level);

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
};

#endif  // ENTITY_H
