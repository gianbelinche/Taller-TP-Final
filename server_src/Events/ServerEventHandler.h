#ifndef SERVEREVENTHANDLER_H
#define SERVEREVENTHANDLER_H

#include <cstdint>

#include "Events/EntityClick.h"
#include "Events/InventoryClick.h"
#include "Events/MessageSent.h"
#include "Events/ServerEventListener.h"
#include "Events/UserMoved.h"
#include "GameState.h"
#include "Thread.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define STOP 4

class ServerEventHandler {
 private:
  GameState &world;
  ServerEventListener &listener;

 public:
  explicit ServerEventHandler(GameState &state,
                              ServerEventListener &eventListener);

  ~ServerEventHandler();

  void handle(UserMoved &ev);

  void handle(EntityClick &ev);

  void handle(InventoryClick &ev);

  void handle(MessageSent &ev);

  void handleUserAttack(EntityClick &ev);
};

#endif  // SERVEREVENTHANDLER_H
