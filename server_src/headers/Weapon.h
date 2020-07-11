#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"
#include "Item.h"

class Weapon : public Item {
 private:
  int minDmg;
  int maxDmg;
  int range;
  int manaRequired;

 public:
  Weapon(int itemID, int itemType, int minDMG, int maxDMG, int rang,
         int manaReq, std::string itemName, int buyPrice, int sellPrice);

  ~Weapon();

  int getAttackRange();

  int getMinDmg();

  int getMaxDmg();

  int getManaReq();

  int beEquiped(PlayerNet* player) override;

};

#endif  // WEAPON_H
