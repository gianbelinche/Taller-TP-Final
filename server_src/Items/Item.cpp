#include "../headers/Item.h"

#include "../headers/PlayerNet.h"

Item::Item(int itemID, int itemType, std::string itemName, int buyPrice,
           int sellPrice)
    : id(itemID),
      typeOfItem(itemType),
      name(itemName),
      buyPrice(buyPrice),
      sellPrice(sellPrice) {}

Item::~Item() {}

int Item::getId() { return id; }

int Item::beEquiped(PlayerNet* player) {
  return 0;
}

int Item::getItemType() { return typeOfItem; }

std::string Item::getItemName() { return name; }

int Item::getBuyPrice() { return buyPrice; }

int Item::getSellPrice() { return sellPrice; }
