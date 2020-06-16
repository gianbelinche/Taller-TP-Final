#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
  int x;
  int y;
public:
  Entity(int x, int y);

  ~Entity();

  virtual void update();
};

#endif // ENTITY_H
