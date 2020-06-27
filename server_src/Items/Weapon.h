#ifndef WEAPON_H
#define WEAPON_H

#include "../Entities/Entity.h"
#include "Item.h"

class Weapon : public Item {
 private:
  int minDmg;
  int maxDmg;
  int range;

 public:
  Weapon(int itemID, int minDMG, int maxDMG, int rang);

  ~Weapon();

  int attack(Entity* entity, int strength);

  int getAttackRange();

  int getMinDmg();

  int getMaxDmg();
};

#endif  // WEAPON_H
