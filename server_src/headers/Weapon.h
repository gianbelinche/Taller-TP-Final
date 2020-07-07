#ifndef WEAPON_H
#define WEAPON_H

#include "Entity.h"
#include "Item.h"

class Weapon : public Item {
 private:
  int minDmg;
  int maxDmg;
  int range;

 public:
  Weapon(int itemID, int itemType, int minDMG, int maxDMG, int rang,
         std::string itemName, int buyPrice, int sellPrice);

  ~Weapon();

  int attack(Entity* entity, int strength);

  int getAttackRange();

  int getMinDmg();

  int getMaxDmg();

  void beEquiped(PlayerNet* player) override;

};

#endif  // WEAPON_H
