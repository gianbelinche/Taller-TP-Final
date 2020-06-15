#ifndef SERVEREVENTHANDLER_H
#define SERVEREVENTHANDLER_H

#include "GameState.h"
#include "Thread.h"
#include "Events/UserMoved.h"

class ServerEventHandler {
private:
  GameState &world;
public:
  ServerEventHandler(GameState &state);

  ~ServerEventHandler();

  void handle(UserMoved ev);
};

#endif // SERVEREVENTHANDLER_H
