#ifndef INVENTORY_H
#define INVENTORY_H

#include <unordered_map>

#include "Item.h"

#define INVENTORY_SIZE 20

class Inventory {
 private:
  std::unordered_map<int, Item*> items;

 public:
  Inventory();

  ~Inventory();

  int getSpaceLeft();

  Item* getItem(int slot);

  int getSize();

  void removeItemAt(int slot);

  bool isFull();

  // Devuelve el numero de slot en el que fue insertado el elemento
  int addItem(Item* item);
};

#endif // INVENTORY_H
