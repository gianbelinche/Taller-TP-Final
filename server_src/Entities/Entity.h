#ifndef ENTITY_H
#define ENTITY_H

class Entity {
 protected:
  int x;
  int y;
  int id;  // Valor numerico que identifica a la entida en el cliente y el
           // server
  int currentFrame;
  int hp;

 public:
  Entity(int x, int y, int id, int hp);

  ~Entity();

  int getId();

  int getX();

  int getY();

  void setX(int new_x);

  void setY(int new_y);

  virtual void update();

  bool isAlive();

  int virtual takeDamage(int dmgToTake) = 0;
};

#endif  // ENTITY_H
