#include "../headers/Inventory.h"

Inventory::Inventory() {}

Inventory::~Inventory() {
  for (auto& item: items) {
    delete item.second;
  }
}

int Inventory::getSpaceLeft() {
  return INVENTORY_SIZE - items.size();
}

int Inventory::getSize() {
  return INVENTORY_SIZE;
}

Item* Inventory::getItem(int slot) {
  if (items.find(slot) != items.end()) {
    return items[slot];
  }
  return nullptr;
}

// Pre: Hay un item en el slot
void Inventory::removeItemAt(int slot) {
  items.erase(slot);
}

bool Inventory::isFull() {
  return items.size() >= INVENTORY_SIZE;
}



