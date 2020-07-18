#include "../headers/Armor.h"

#include "../headers/PlayerNet.h"

Armor::Armor(int id, int itemType, int minDef, int maxDef,
             std::string& itemName, int buyPrice, int sellPrice)
    : Wearable(id, itemType, minDef, maxDef, itemName, buyPrice, sellPrice) {}

Armor::~Armor() {}

int Armor::beEquiped(PlayerNet* player) {
  player->equipArmor(static_cast<Armor*>(this));
  return 0;
}
