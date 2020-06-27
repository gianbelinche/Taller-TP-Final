#include "Weapon.h"

#include "../config/Equations.h"

Weapon::Weapon(int itemID, int minDMG, int maxDMG, int rang)
    : Item(itemID), minDmg(minDMG), maxDmg(maxDMG), range(rang) {}

Weapon::~Weapon() {}

int Weapon::attack(Entity* entity, int strength) {
  int hitDamage = equation::causedDamage(strength, minDmg, maxDmg);
  return entity->takeDamage(hitDamage);
}

int Weapon::getMinDmg() { return minDmg; }

int Weapon::getMaxDmg() { return maxDmg; }

int Weapon::getAttackRange() {
  return range;
}
