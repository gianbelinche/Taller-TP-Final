#ifndef ENTITY_H
#define ENTITY_H

class Entity {
protected:
  int x;
  int y;
public:
  Entity();

  ~Entity();

  virtual void update();
};

#endif // ENTITY_H
