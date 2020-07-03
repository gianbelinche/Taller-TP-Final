#ifndef ENTITYCLICK_H
#define ENTITYCLICK_H

#include "Event.h"

class EntityClick : public Event {
 private:
  int destinyId;

 public:
  EntityClick(int originUser, int destinyEntity);

  ~EntityClick();

  int getDestinyEntityID();
};

#endif // ENTITYCLICK_H
