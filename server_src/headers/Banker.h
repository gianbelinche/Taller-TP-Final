#include "NPC.h"
#include "Bank.h"
#include "ServerEventListener.h"

class Banker : public NPC {
private:
  Bank& bank;
public:
  Banker(int id, int x, int y, ServerEventListener& eventListener,Bank& bank);

  ~Banker();

  void listItems(PlayerNet* player) override;

  void goldDeposit(PlayerNet* player, int amount) override;

  void goldExtraction(PlayerNet* player, int amount) override;

  void depositItem(Item* item, int id) override;
};


