#ifndef HELMET_H
#define HELMET_H

#include "Wearable.h"

class Helmet : public Wearable {
 private:
 public:
  Helmet(int id, int itemType, int minDef, int maxDef, std::string itemName,
         int buyPrice, int sellPrice);

  ~Helmet();

  int beEquiped(PlayerNet* player) override;
};

#endif  // HELMET_H
