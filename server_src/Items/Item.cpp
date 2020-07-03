#include "../headers/Item.h"
#include "../headers/PlayerNet.h"

Item::Item(int itemID) {}

Item::~Item() {}

int Item::getId() { return id; }

void Item::beEquiped(PlayerNet &player) {}
