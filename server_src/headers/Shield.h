#ifndef SHIELD_H
#define SHIELD_H

#include "Wearable.h"

class Shield : public Wearable {
 private:
 public:
  Shield(int id, int itemType, int minDef, int maxDef, std::string itemName,
         int buyPrice, int sellPrice);

  ~Shield();

  int beEquiped(PlayerNet* player) override;
};

#endif  // SHIELD_H
