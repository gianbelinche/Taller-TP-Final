#include "../headers/ManaPotion.h"

#include "../headers/PlayerNet.h"

ManaPotion::ManaPotion(int itemId, int itemType, std::string& itemName,
                       int buyPrice, int sellPrice, int manaRecovery)
    : Item(itemId, itemType, itemName, buyPrice, sellPrice),
      manaRecovery(manaRecovery) {}

ManaPotion::~ManaPotion() {}

int ManaPotion::beEquiped(PlayerNet* player) {
  player->recoverMana(manaRecovery);
  return -1;
}