#ifndef USERMOVED_H
#define USERMOVED_H

#include "Event.h"

class UserMoved : public Event {
private:
  char direction;
public:
  UserMoved(int originUser, char direction);

  ~UserMoved();
};

#endif // USERMOVED_H
