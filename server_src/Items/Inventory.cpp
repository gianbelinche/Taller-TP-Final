#include "../headers/Inventory.h"

#include <iostream>

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
  std::unordered_map<int,Item*> new_inventory;
  for (int i = 0; i < INVENTORY_SIZE;i++){
    if (items.find(i) != items.end()){
      if (i < slot){
        new_inventory[i] = items[i];
      } else if (i > slot){
        new_inventory[i-1] = items[i];
      }
    }
  }
  this->items = std::move(new_inventory);
}

bool Inventory::isFull() {
  return items.size() >= INVENTORY_SIZE;
}

int Inventory::addItem(Item* item) {
  for (int i = 0; i < INVENTORY_SIZE; i++) {
    if (items.find(i) == items.end()) { // Esta vacio
      items[i] = item;
      return i;
    }
  }
  return -1;
}
