#include "../headers/Item.h"
#include "../headers/PlayerNet.h"

Item::Item(int itemID, int itemType, std::string itemName) {}

Item::~Item() {}

int Item::getId() { return id; }

void Item::beEquiped(PlayerNet &player) {}

int Item::getItemType() {
  return typeOfItem;
}

std::string Item::getItemName() {
  return name;
}


