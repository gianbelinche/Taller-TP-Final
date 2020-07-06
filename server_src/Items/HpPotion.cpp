#include "../headers/HpPotion.h"

HpPotion::HpPotion(int itemId, int itemType, std::string itemName, int buyPrice,
                   int sellPrice, int hpRecovery)
    : Item(itemId, itemType, itemName, buyPrice, sellPrice),
      hpRecovery(hpRecovery) {}

HpPotion::~HpPotion() {}