#include "../headers/Shield.h"

#include "../headers/PlayerNet.h"

Shield::Shield(int id, int itemType, int minDef, int maxDef,
               std::string& itemName, int buyPrice, int sellPrice)
    : Wearable(id, itemType, minDef, maxDef, itemName, buyPrice, sellPrice) {}

Shield::~Shield() {}

int Shield::beEquiped(PlayerNet* player) {
  player->equipShield(static_cast<Shield*>(this));
  return 0;
}
