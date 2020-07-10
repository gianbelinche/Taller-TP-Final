#include "../headers/GoldDrop.h"
#include "../headers/PlayerNet.h"

GoldDrop::GoldDrop(int itemId, int itemType, std::string itemName,
                   int goldAmount)
    : Item(itemId, itemType, itemName, 0, 0), amount(goldAmount) {}

GoldDrop::~GoldDrop() {}

int GoldDrop::beTaken(PlayerNet* player) {
  int goldPlayerCanTake = player->getMaxGold() - player->getGold();
  if (goldPlayerCanTake >= amount) {
    player->addGold(amount);
    return 0;
  } else { // Si superaria el oro maximo tomando todo, entonces toma una parte
    player->addGold(goldPlayerCanTake);
    amount -= goldPlayerCanTake;
    return -1;
  }
}