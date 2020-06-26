#include "Weapon.h"

#include "../config/Equations.h"

Weapon::Weapon(int itemID, int minDMG, int maxDMG)
    : Item(itemID), minDmg(minDMG), maxDmg(maxDMG) {}

Weapon::~Weapon() {}

int Weapon::attack(Entity* entity, int strength) {
  int hitDamage = equation::causedDamage(strength, minDmg, maxDmg);
  return entity->takeDamage(hitDamage);
}

int Weapon::getMinDmg() { return minDmg; }

int Weapon::getMaxDmg() { return maxDmg; }
