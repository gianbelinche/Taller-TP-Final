#include "../headers/Bank.h"

Bank::Bank() {}

Bank::~Bank() {}

std::vector<Item*>& Bank::getUserItems(int id) {
  return lockers[id].getItems(); // Se crea si no existe
}

void Bank::addGoldTo(int id) {

}
