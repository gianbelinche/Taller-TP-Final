#include "../headers/Wearable.h"

Wearable::Wearable(int id, int itemType, int minDEF, int maxDEF,
                   std::string itemName, int buyPrice, int sellPrice)
    : Item(id, itemType, itemName, buyPrice, sellPrice),
      minDefense(minDEF),
      maxDefense(maxDEF) {}

Wearable::~Wearable() {}

int Wearable::getMinDef() { return minDefense; }

int Wearable::getMaxDef() { return maxDefense; }
