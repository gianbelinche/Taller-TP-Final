#ifndef SERVEREVENTHANDLER_H
#define SERVEREVENTHANDLER_H

#include <cstdint>

#include "EntityClick.h"
#include "InventoryClick.h"
#include "MessageSent.h"
#include "PlayerConnection.h"
#include "ServerEventListener.h"
#include "UserMoved.h"
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

  void handle(PlayerConnection &ev);

  void handleUserAttack(EntityClick &ev);

  void handleMeditation(int playerId);

  void handleResurrect(int playerId);

  void handleHeal(int playerId);

  void handleDeposit(int playerId, int slotChoice);

  void handleItemSubstraction(int playerId, int itemChoice);
};

#endif  // SERVEREVENTHANDLER_H
