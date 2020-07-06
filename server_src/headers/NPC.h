#ifndef NPC_H
#define NPC_H

#include <unordered_set>
#include <vector>

#include "Entity.h"
#include "Item.h"
#include "MasterFactory.h"
#include "ServerEventListener.h"

// Don't touch this
#define NPCMAXHP 999999
#define NPCLEVEL 999

class PlayerNet;

class NPC : public Entity {
 protected:
  std::vector<Item*> itemsAvailable;
  ServerEventListener& listener;
  MasterFactory& factory;

 public:
  NPC(int id, int x, int y, ServerEventListener& eventListener,
      MasterFactory& factory);

  ~NPC();

  virtual void listItems(PlayerNet* player);

  std::string getPrettyPrint(std::vector<Item*> items);

  virtual void goldDeposit(PlayerNet* player, int amount);

  virtual void goldExtraction(PlayerNet* player, int amount);

  virtual void depositItem(Item* item, int id);

  virtual Item* substractItem(int choice, int id);

  virtual int sellItem(Item* item);

  virtual Item* buyItem(PlayerNet* player, int choice);

  virtual void heal(PlayerNet* player);

  virtual void resurrect(PlayerNet* player);
};

#endif  // NPC_H
