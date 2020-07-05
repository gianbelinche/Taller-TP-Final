#include "../headers/Wearable.h"

Wearable::Wearable(int id, int itemType, int minDEF, int maxDEF)
    : Item(id, itemType), minDefense(minDEF), maxDefense(maxDEF) {}

Wearable::~Wearable() {}

int Wearable::getMinDef() { return minDefense; }

int Wearable::getMaxDef() { return maxDefense; }
