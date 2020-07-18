#include "../headers/Helmet.h"

#include "../headers/PlayerNet.h"

Helmet::Helmet(int id, int itemType, int minDef, int maxDef,
               std::string& itemName, int buyPrice, int sellPrice)
    : Wearable(id, itemType, minDef, maxDef, itemName, buyPrice, sellPrice) {}

Helmet::~Helmet() {}

int Helmet::beEquiped(PlayerNet* player) {
  player->equipHelmet(static_cast<Helmet*>(this));
  return 0;
}
