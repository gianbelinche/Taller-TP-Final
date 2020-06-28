#ifndef SERVEREVENTHANDLER_H
#define SERVEREVENTHANDLER_H

#include "Events/ClickEvent.h"
#include "Events/UserMoved.h"
#include "GameState.h"
#include "Thread.h"

class ServerEventHandler {
 private:
  GameState &world;

 public:
  explicit ServerEventHandler(GameState &state);

  ~ServerEventHandler();

  bool handle(UserMoved &ev);

  void handleUserAttack(ClickEvent &ev);
};

#endif  // SERVEREVENTHANDLER_H
