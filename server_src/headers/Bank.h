#ifndef BANK_H
#define BANK_H

#include "BankLocker.h"
#include "Item.h"

#include <unordered_map>

class Bank {
private:
  std::unordered_map<int, BankLocker> lockers;
public:
  Bank();

  ~Bank();

  std::vector<Item*>& getUserItems(int id);

  void addGoldTo(int id, int amount);

  void substractGoldTo(int id, int amount);

  int getUserGold(int id);

  void addItemToUser(int id, Item* item);

  Item* substractItem(int choice, int id);
};

#endif // BANK_H
