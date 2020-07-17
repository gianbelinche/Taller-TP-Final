#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <vector>

#include "Configuration.h"

class PlayerNet;

class Item {
 private:
  int id;
  int typeOfItem;
  std::string name;
  int buyPrice;
  int sellPrice;
  int equipped_position;

 public:
  Item(int itemID, int itemType, std::string itemName, int buyPrice,
       int sellPrice);

  virtual ~Item();

  int getId();

  int getItemType();

  std::string getItemName();

  virtual int beEquiped(PlayerNet* player);

  virtual int beTaken(PlayerNet* player);

  int getBuyPrice();

  int getSellPrice();

  int getEquippedPosition();

  std::vector<uint32_t> getSendable();

};

#endif  // ITEM_H
