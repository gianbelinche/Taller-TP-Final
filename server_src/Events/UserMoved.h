#ifndef USERMOVED_H
#define USERMOVED_H

#include "Event.h"

class UserMoved : public Event {
 private:
  char direction;

 public:
  UserMoved(int originUser, char direction);

  ~UserMoved();

  UserMoved(const UserMoved& other) = delete;

  UserMoved& operator=(const UserMoved& other) = delete;

  UserMoved(UserMoved&& other);

  UserMoved& operator=(UserMoved&& other);

  char getDirection();
};

#endif  // USERMOVED_H
