#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
  int x;
  int y;
  int id; // Valor numerico que identifica a la entida en el cliente y el server
  int currentFrame;
public:
  Entity(int x, int y, int id);

  ~Entity();

  int getX();

  int getY();

  void setX(int new_x);

  void setY(int new_y);

  virtual void update();
};

#endif // ENTITY_H
