#ifndef HPPOTION_H
#define HPPOTION_H

#include "Item.h"

class HpPotion : public Item {
 private:
  int hpRecovery;

 public:
  HpPotion(int itemID, int itemType, std::string itemName, int buyPrice,
           int sellPrice, int hpRecovery);

  ~HpPotion();

  int beEquiped(PlayerNet* player) override;
};

#endif  // HPPOTION_H
