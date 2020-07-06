#include "../headers/Armor.h"

Armor::Armor(int id, int itemType, int minDef, int maxDef, std::string itemName,
             int buyPrice, int sellPrice)
    : Wearable(id, itemType, minDef, maxDef, itemName, buyPrice, sellPrice) {}

Armor::~Armor() {}
