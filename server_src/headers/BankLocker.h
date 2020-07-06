#include "Item.h"

#include <vector>

class BankLocker
{
private:
  int gold;
  std::vector<Item*> itemsInside;
public:
  BankLocker();

  ~BankLocker();

  std::vector<Item*>& getItems();

  void addGold(int amount);

  void substractGold(int amount);

  int getGold();

  void addItem(Item* item);
};

