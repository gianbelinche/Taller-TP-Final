#ifndef NPC_H
#define NPC_H

#include <vector>

#include "Entity.h"
#include "Item.h"
#include "ServerEventListener.h"

// Don't touch this
#define NPCMAXHP 999999
#define NPCLEVEL 999

class PlayerNet;

class NPC : public Entity {
 protected:
  std::vector<Item*> itemsAvailable;
  ServerEventListener& listener;

 public:
  NPC(int id, int x, int y, ServerEventListener& eventListener);

  ~NPC();

  void virtual listItems(PlayerNet* player);

  std::string getPrettyPrint(std::vector<Item*> items);

  void virtual goldDeposit(PlayerNet* player, int amount);

  void virtual goldExtraction(PlayerNet* player, int amount);

  void virtual depositItem(Item* item, int id);
};

#endif // NPC_H
