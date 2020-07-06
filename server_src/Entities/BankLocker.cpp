#include "../headers/BankLocker.h"

BankLocker::BankLocker() : gold(0) {}

BankLocker::~BankLocker() {}

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

