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

  virtual void listItems(PlayerNet* player);

  std::string getPrettyPrint(std::vector<Item*> items);

  virtual void goldDeposit(PlayerNet* player, int amount);

  virtual void goldExtraction(PlayerNet* player, int amount);

  virtual void depositItem(Item* item, int id);

  virtual Item* substractItem(int choice, int id);

  virtual int sellItem(Item* item);
};

#endif // NPC_H
