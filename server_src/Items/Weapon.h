#ifndef WEAPON_H
#define WEAPON_H

#include "../Entities/Entity.h"
#include "Item.h"

class Weapon : public Item {
 private:
  int minDmg;
  int maxDmg;

 public:
  Weapon(int itemID, int minDMG, int maxDMG);

  ~Weapon();

  int attack(Entity* entity, int strength);

  int virtual getAttackRange() = 0;

  int getMinDmg();

  int getMaxDmg();
};

#endif  // WEAPON_H
