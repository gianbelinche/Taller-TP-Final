#ifndef ITEM_H
#define ITEM_H

class PlayerNet;

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
