#ifndef GOLDDROP_H
#define GOLDDROP_H

#include "Item.h"

class GoldDrop : public Item {
private:
  int amount;
public:
  GoldDrop(int itemId, int itemType, std::string& itemName, int goldAmount);

  ~GoldDrop();

  int beTaken(PlayerNet* player) override;
};

#endif // GOLDDROP_H
