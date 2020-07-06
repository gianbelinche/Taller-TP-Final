#ifndef ITEM_H
#define ITEM_H

#include "Configuration.h"

#include <string>

class PlayerNet;

class Item {
 private:
  int id;
  int typeOfItem;
  std::string name;
 public:
  Item(int itemID, int itemType, std::string itemName);

  ~Item();

  int getId();

  int getItemType();

  std::string getItemName();

  void virtual beEquiped(PlayerNet &player);
};

#endif  // ITEM_H
