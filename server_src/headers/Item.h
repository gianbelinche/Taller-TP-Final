#ifndef ITEM_H
#define ITEM_H

#include <string>

#include "Configuration.h"

class PlayerNet;

class Item {
 private:
  int id;
  int typeOfItem;
  std::string name;
  int buyPrice;
  int sellPrice;

 public:
  Item(int itemID, int itemType, std::string itemName, int buyPrice,
       int sellPrice);

  virtual ~Item();

  int getId();

  int getItemType();

  std::string getItemName();

  virtual int beEquiped(PlayerNet* player);

  int getBuyPrice();

  int getSellPrice();
};

#endif  // ITEM_H
