#ifndef ITEM_H
#define ITEM_H

class PlayerNet;

class Item {
 private:
  int id;
  int typeOfItem;

 public:
  Item(int itemID, int itemType);

  ~Item();

  int getId();

  int getItemType();

  void virtual beEquiped(PlayerNet &player);
};

#endif  // ITEM_H
