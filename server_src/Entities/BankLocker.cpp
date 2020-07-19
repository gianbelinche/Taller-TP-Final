#include "../headers/BankLocker.h"

BankLocker::BankLocker() : gold(0) {}

BankLocker::~BankLocker() {
  for (auto& item: itemsInside) {
    delete item;
  }
}

std::vector<Item*>& BankLocker::getItems() {
  return itemsInside;
}

void BankLocker::addGold(int amount) {
  gold += amount;
}

void BankLocker::substractGold(int amount) {
  gold -= amount;
}

int BankLocker::getGold() {
  return gold;
}

void BankLocker::addItem(Item* item) {
  itemsInside.push_back(item);
}

Item* BankLocker::getItem(int itemType) {
  Item* itemTaken = nullptr;
  for (size_t i = 0; i < itemsInside.size(); i++) {
    if (itemsInside[i]->getItemType() == itemType) {
      itemTaken = itemsInside[i];
      itemsInside.erase(itemsInside.begin() + i);
      break;
    }
  }
  return itemTaken;
}


