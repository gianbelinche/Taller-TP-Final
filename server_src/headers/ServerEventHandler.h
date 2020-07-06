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
#include "NPC.h"

#define UP 0
#define DOWN 1
#define LEFT 2  NPC* npc = world.getNpc(player->getSelectedNpc());

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

  bool npcHandleVerification(int playerId);

  void handleMeditation(int playerId);

  void handleResurrect(int playerId, NPC* npc);

  void handleHeal(int playerId, NPC* npc);

  void handleItemDeposit(int playerId, int slotChoice, NPC* npc);

  void handleGoldDeposit(int playerId, int slotChoice, NPC* npc);

  void handleItemSubstraction(int playerId, int itemChoice, NPC* npc);

  void handleGoldSubstraction(int playerId, int amount, NPC* npc);

  void handleListItems(int playerId, NPC* npc);

  void handlePurchase(int playerId, int itemChoice, NPC* npc);

  void handleSell(int playerId, NPC* npc, int slotChoice=-1);

  void handleTake(int playerId);

  void handleDrop(int playerId, int slotChoice=-1);

  void handlePlayerMsg(int playerId, int otherPlayerId=-1);
};

#endif  // SERVEREVENTHANDLER_H
