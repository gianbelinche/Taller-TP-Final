#include "../headers/Armor.h"

Armor::Armor(int id, int itemType, int minDef, int maxDef)
    : Wearable(id, itemType, minDef, maxDef) {}

Armor::~Armor() {}
