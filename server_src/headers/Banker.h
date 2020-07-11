#ifndef BANKER_H
#define BANKER_H

#include "Bank.h"
#include "Item.h"
#include "NPC.h"
#include "ServerEventListener.h"

class MasterFactory;
class Banker : public NPC {
 private:
  Bank& bank;

 public:
  Banker(int id, int x, int y, ServerEventListener& eventListener,
         MasterFactory& factory, Bank& bank);

  ~Banker();

  void listItems(PlayerNet* player) override;

  void goldDeposit(PlayerNet* player, int amount) override;

  void goldExtraction(PlayerNet* player, int amount) override;

  void depositItem(Item* item, int id) override;

  Item* substractItem(int choice, int id) override;

  int sellItem(Item* item) override;

  Item* buyItem(PlayerNet* player, int choice) override;

  std::unordered_map<uint32_t,std::vector<uint32_t>> getData();
};

#endif // BANKER_H
