#ifndef USERMOVED_H
#define USERMOVED_H

#include "Event.h"

class UserMoved : public Event {
private:
  int x;
  int y;
public:
  UserMoved(int originUser, int pos_x, int pos_y);

  ~UserMoved();

  int getX();

  int getY();
};

#endif // USERMOVED_H
