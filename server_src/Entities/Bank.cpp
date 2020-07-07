#include "../headers/Bank.h"


Bank::Bank() {}

Bank::~Bank() {}

std::vector<Item*>& Bank::getUserItems(int id) {
  return lockers[id].getItems(); // Se crea si no existe
}

void Bank::addGoldTo(int id, int amount) {
  lockers[id].addGold(amount);
}

void Bank::substractGoldTo(int id, int amount) {
  lockers[id].substractGold(amount);
}

int Bank::getUserGold(int id) {
  return lockers[id].getGold();
}

void Bank::addItemToUser(int id, Item* item) {
  lockers[id].addItem(item);
}

Item* Bank::substractItem(int choice, int id) {
  return lockers[id].getItem(choice);
}

