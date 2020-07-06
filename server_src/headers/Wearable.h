#ifndef WEARABLE_H
#define WEARABLE_H

#include "Item.h"

class Wearable : public Item {
 private:
  int minDefense;
  int maxDefense;

 public:
  Wearable(int id, int itemType, int minDEF, int maxDEF, std::string itemName,
           int buyPrice, int sellPrice);

  ~Wearable();

  int getMinDef();

  int getMaxDef();
};

#endif  // WEARABLE_H
