#include "../headers/Wearable.h"

Wearable::Wearable(int id, int minDEF, int maxDEF)
    : Item(id), minDefense(minDEF), maxDefense(maxDEF) {}

Wearable::~Wearable() {}

int Wearable::getMinDef() { return minDefense; }

int Wearable::getMaxDef() { return maxDefense; }
