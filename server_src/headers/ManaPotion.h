#ifndef MANAPOTION_H
#define MANAPOTION_H

#include "Item.h"
class ManaPotion : public Item {
 private:
  int manaRecovery;

 public:
  ManaPotion(int itemId, int itemType, std::string& itemName, int buyPrice,
             int sellPrice, int manaRecovery);
             
  ~ManaPotion();

  int beEquiped(PlayerNet* player) override;
};

#endif // MANAPOTION_H
