#ifndef HELMET_H
#define HELMET_H

#include "Wearable.h"

class Helmet : public Wearable {
 private:
 public:
  Helmet(int id, int itemType, int minDef, int maxDef, std::string itemName,
         int buyPrice, int sellPrice);

  ~Helmet();
};

#endif  // HELMET_H
