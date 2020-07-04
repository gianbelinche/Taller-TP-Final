#ifndef PLAYERCONNECTION_H
#define PLAYERCONNECTION_H

#include "Event.h"

class PlayerConnection : public Event {
private:
  
public:
  PlayerConnection(int id);

  ~PlayerConnection();
};

#endif // PLAYERCONNECTION_H
