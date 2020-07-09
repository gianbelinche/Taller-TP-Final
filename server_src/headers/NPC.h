#ifndef NPC_H
#define NPC_H

#include <unordered_set>
#include <vector>

#include "Entity.h"
#include "Item.h"
#include "ServerEventListener.h"

// Don't touch this
#define NPCMAXHP 999999
#define NPCLEVEL 999

#define BANKER_TYPE 0
#define MERCHANT_TYPE 1
#define PRIEST_TYPE 2

class MasterFactory;
class PlayerNet;

class NPC : public Entity {
 protected:
  std::vector<Item*> itemsAvailable;
  ServerEventListener& listener;
  MasterFactory& factory;
  int npcType;

 public:
  NPC(int id, int x, int y, ServerEventListener& eventListener,
      MasterFactory& factory);

  virtual ~NPC();

  int getNpcType();

  virtual void listItems(PlayerNet* player);

  std::string getPrettyPrint(Item* item);

  virtual void goldDeposit(PlayerNet* player, int amount);

  virtual void goldExtraction(PlayerNet* player, int amount);

  virtual void depositItem(Item* item, int id);

  virtual Item* substractItem(int choice, int id);

  virtual int sellItem(Item* item);

  virtual Item* buyItem(PlayerNet* player, int choice);

  virtual void heal(PlayerNet* player);

  virtual void resurrect(PlayerNet* player);

  bool canBeAttackedBy(Entity* ent) override;

  int takeDamage(int dmgToTake) override;

  std::vector<uint32_t> getSendable() override;

};

#endif  // NPC_H
