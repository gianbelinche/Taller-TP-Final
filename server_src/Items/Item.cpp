#include "../headers/Item.h"

#include "../headers/PlayerNet.h"

enum items{
    EMPTY,
    SWORD,
    AXE,
    HAMMER,
    FRESNO_ROD,
    ELFIC_FLUTE,
    BACULO_NUDOSO,
    BACULO_ENGARZADO,
    SIMPLE_BOW,
    COMPOSED_BOW,
    LEATHER_ARMOR,
    PLATE_ARMOR,
    BLUE_TUNIC,
    HOOD,
    IRON_HELMET,
    TURTLE_SHIELD,
    IRON_SHIELD,
    MAGIC_HAT,
    LIFE_POTION,
    MANA_POTION
};

#define NO_EQUIPPED_TYPE -1
#define EQUIPPED_TYPE_0 0
#define EQUIPPED_TYPE_1 1
#define EQUIPPED_TYPE_2 2
#define EQUIPPED_TYPE_3 3

Item::Item(int itemID, int itemType, std::string itemName, int buyPrice,
           int sellPrice)
    : id(itemID),
      typeOfItem(itemType),
      name(itemName),
      buyPrice(buyPrice),
      sellPrice(sellPrice) {
  std::unordered_map<int,int> equipped;
  equipped[EMPTY] = NO_EQUIPPED_TYPE;
  equipped[SWORD] = EQUIPPED_TYPE_0;
  equipped[AXE] = EQUIPPED_TYPE_0;
  equipped[HAMMER] = EQUIPPED_TYPE_0;
  equipped[FRESNO_ROD] = EQUIPPED_TYPE_0;
  equipped[ELFIC_FLUTE] = EQUIPPED_TYPE_0;
  equipped[BACULO_NUDOSO] = EQUIPPED_TYPE_0;
  equipped[BACULO_ENGARZADO] = EQUIPPED_TYPE_0;
  equipped[SIMPLE_BOW] = EQUIPPED_TYPE_0;
  equipped[COMPOSED_BOW] = EQUIPPED_TYPE_0;
  equipped[LEATHER_ARMOR] = EQUIPPED_TYPE_1;
  equipped[PLATE_ARMOR] = EQUIPPED_TYPE_1;
  equipped[BLUE_TUNIC] = EQUIPPED_TYPE_1;
  equipped[HOOD] = EQUIPPED_TYPE_3;
  equipped[IRON_HELMET] = EQUIPPED_TYPE_3;
  equipped[TURTLE_SHIELD] = EQUIPPED_TYPE_2;
  equipped[IRON_SHIELD] = EQUIPPED_TYPE_2;
  equipped[MAGIC_HAT] = EQUIPPED_TYPE_3;
  equipped[LIFE_POTION] = NO_EQUIPPED_TYPE;
  equipped[MANA_POTION] = NO_EQUIPPED_TYPE;

  equipped_position = equipped[itemType];
}

Item::~Item() {}

int Item::getId() { return id; }

int Item::beEquiped(PlayerNet* player) {
  return 0;
}

int Item::beTaken(PlayerNet* player) {
  player->addItemToInventory(this);
  return 0;
}

int Item::getItemType() { return typeOfItem; }

std::string Item::getItemName() { return name; }

int Item::getBuyPrice() { return buyPrice; }

int Item::getSellPrice() { return sellPrice; }

int Item::getEquippedPosition(){ return equipped_position; }

std::vector<uint32_t> Item::getSendable() {
  std::vector<uint32_t> itemInfo = {3};
  itemInfo.push_back(id);
  itemInfo.push_back(typeOfItem);
  return itemInfo;
}