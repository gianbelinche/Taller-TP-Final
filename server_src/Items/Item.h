#ifndef ITEM_H
#define ITEM_H

#include "../Entities/PlayerNet.h"

class Item {
 private:
  int id;

 public:
  Item(int itemID);

  ~Item();

  int getId();

  void virtual beEquiped(PlayerNet &player);
};

#endif  // ITEM_H
