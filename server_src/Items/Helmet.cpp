#include "../headers/Helmet.h"

Helmet::Helmet(int id, int itemType, int minDef, int maxDef,
               std::string itemName, int buyPrice, int sellPrice)
    : Wearable(id, itemType, minDef, maxDef, itemName, buyPrice, sellPrice) {}

Helmet::~Helmet() {}
