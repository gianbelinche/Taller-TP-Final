#ifndef SERVEREVENTHANDLER_H
#define SERVEREVENTHANDLER_H

#include <cstdint>

#include "Configuration.h"
#include "EntityClick.h"
#include "GameState.h"
#include "InventoryClick.h"
#include "MessageSent.h"
#include "NPC.h"
#include "PlayerConnection.h"
#include "ServerEventListener.h"
#include "Thread.h"
#include "UserMoved.h"

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define STOP 4

class ServerEventHandler {
 private:
  GameState &world;
  ServerEventListener &listener;
  Configuration &config;

 public:
  explicit ServerEventHandler(GameState &state,
                              ServerEventListener &eventListener,
                              Configuration &configuration);

  ~ServerEventHandler();

  void handle(UserMoved &ev);

  void handle(EntityClick &ev);

  void handle(InventoryClick &ev);

  void handle(MessageSent &ev);

  void handle(PlayerConnection &ev);

  void handleUserAttack(EntityClick &ev);

  bool npcHandleVerification(int playerId);

  void handleMeditation(int playerId);

  void handleResurrect(int playerId);

  void handleHeal(int playerId, NPC *npc);

  void handleItemDeposit(int playerId, int slotChoice, NPC *npc);

  void handleGoldDeposit(int playerId, int slotChoice, NPC *npc);

  void handleItemSubstraction(int playerId, int itemChoice, NPC *npc);

  void handleGoldSubstraction(int playerId, int amount, NPC *npc);

  void handleListItems(int playerId, NPC *npc);

  void handlePurchase(int playerId, int itemChoice, NPC *npc);

  void handleSell(int playerId, NPC *npc, int slotChoice = -1);

  void handleTake(int playerId);

  void handleDrop(int playerId, int slotChoice = -1);

  void handlePlayerMsg(int playerId, std::string msg, int otherPlayerId = -1);

  void handleEquip(int playerId);

  void handleRemoveInventoryItem(int playerId, int slot);
};

#endif  // SERVEREVENTHANDLER_H
