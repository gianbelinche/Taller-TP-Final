#include "../headers/Weapon.h"

#include "../headers/Equations.h"
#include "../headers/PlayerNet.h"

Weapon::Weapon(int itemID, int itemType, int minDMG, int maxDMG, int rang,
               int manaReq, std::string itemName, int buyPrice, int sellPrice)
    : Item(itemID, itemType, itemName, buyPrice, sellPrice),
      minDmg(minDMG),
      maxDmg(maxDMG),
      range(rang),
      manaRequired(manaReq) {}

Weapon::~Weapon() {}

int Weapon::attack(Entity* entity, int strength) {
  int hitDamage = equation::causedDamage(strength, minDmg, maxDmg);
  return entity->takeDamage(hitDamage);
}

int Weapon::getMinDmg() { return minDmg; }

int Weapon::getMaxDmg() { return maxDmg; }

int Weapon::getAttackRange() { return range; }

int Weapon::getManaReq() { return manaRequired; }

int Weapon::beEquiped(PlayerNet* player) {
  player->equipWeapon(static_cast<Weapon*>(this));
  return 0;
}

