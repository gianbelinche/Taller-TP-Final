#ifndef ARMOR_H
#define ARMOR_H

#include "Wearable.h"

class Armor : public Wearable {
 private:
 public:
  Armor(int id, int itemType, int minDef, int maxDef, std::string itemName,
        int buyPrice, int sellPrice);

  ~Armor();
};

#endif  // ARMOR_H
