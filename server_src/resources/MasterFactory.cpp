#include "../headers/MasterFactory.h"

#include "../headers/Persistor.h"

MasterFactory::MasterFactory(std::atomic<uint32_t>& idCounter,
                             Configuration& configuration,
                             ServerEventListener& eventListener)
    : idGenerator(idCounter),
      config(configuration),
      listener(eventListener),
      goblin(config, GOBLIN, GOBLIN_TYPE),
      spider(config, SPIDER, SPIDER_TYPE),
      skeleton(config, SKELETON, SKELETON_TYPE),
      zombie(config, ZOMBIE, ZOMBIE_TYPE),
      human(config, HUMAN, HUMAN_ID),
      elf(config, ELF, ELF_ID),
      dwarf(config, DWARF, DWARF_ID),
      gnome(config, GNOME, GNOME_ID),
      warrior(config, WARRIOR, WARRIOR_ID),
      wizard(config, WIZARD, WIZARD_ID),
      cleric(config, CLERIC, CLERIC_ID),
      paladin(config, PALADIN, PALADIN_ID) {
  races[HUMAN_ID] = &human;
  races[ELF_ID] = &elf;
  races[DWARF_ID] = &dwarf;
  races[GNOME_ID] = &gnome;

  classes[WARRIOR_ID] = &warrior;
  classes[WIZARD_ID] = &wizard;
  classes[CLERIC_ID] = &cleric;
  classes[PALADIN_ID] = &paladin;

  Persistor persistor;
  std::unordered_map<uint32_t, std::vector<uint32_t>> data =
      persistor.obtainBank();
  for (auto& player : data) {
    if (player.second.size() > 0) {
      bank.addGoldTo(player.first, (player.second)[0]);
      for (unsigned int i = 1; i < player.second.size(); i++) {
        bank.addItemToUser(player.first, this->createItem((player.second)[i]));
      }
    }
  }
}

MasterFactory::~MasterFactory() {}

Monster* MasterFactory::newGoblin(int x, int y, GameState& world) {
  return goblin.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newSkeleton(int x, int y, GameState& world) {
  return skeleton.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newSpider(int x, int y, GameState& world) {
  return spider.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newZombie(int x, int y, GameState& world) {
  return zombie.newMonster(idGenerator++, x, y, world, listener);
}

PlayerNet* MasterFactory::createPlayer(std::vector<uint32_t>& playerData,
                                       GameState& world) {

  // ACORTAR ESTA FUNCION!!!!!!
  Weapon* weapon;
  Armor* armor;
  Helmet* helmet;
  Shield* shield;

  Weapon* defaultWeapon = createWeapon(NOTHING_TYPE);
  Armor* defaultArmor = createArmor(NOTHING_TYPE);
  Helmet* defaultHelmet = createHelmet(NOTHING_TYPE);
  Shield* defaultShield = createShield(NOTHING_TYPE);

  uint32_t id = playerData[0];
  uint32_t x = playerData[1];
  uint32_t y = playerData[2];
  uint32_t level = playerData[3];
  uint32_t exp = playerData[4];
  Race* playerRace = races[playerData[5]];
  Class* playerClass = classes[playerData[6]];
  uint32_t gold = playerData[7];
  PlayerState* state;
  if (playerData[8] == 0) {
    state = &PlayerState::normal;
  } else {
    state = &PlayerState::dead;
  }

  /* Prevents leaks/double frees later */
  if (playerData[9] == NOTHING_TYPE) {
    weapon = defaultWeapon;
  } else {
    weapon = createWeapon(playerData[9]);
  }

  if (playerData[10] == NOTHING_TYPE) {
    helmet = defaultHelmet;
  } else {
    helmet = createHelmet(playerData[10]);
  }

  if (playerData[11] == NOTHING_TYPE) {
    armor = defaultArmor;
  } else {
    armor = createArmor(playerData[11]);
  }

  if (playerData[12] == NOTHING_TYPE) {
    shield = defaultShield;
  } else {
    shield = createShield(playerData[12]);
  }
  PlayerNet* player =
      new PlayerNet(x, y, id, world, 6, exp, level, gold, weapon, armor, helmet,
                    shield, state, playerClass, playerRace, listener,
                    config.getConfigValue("framesBetweenUpdate"), defaultWeapon,
                    defaultArmor, defaultHelmet, defaultShield);
  // Rm duplicates from inventory
  rmFirstAppearanceOf(playerData, weapon->getItemType());
  rmFirstAppearanceOf(playerData, armor->getItemType());
  rmFirstAppearanceOf(playerData, helmet->getItemType());
  rmFirstAppearanceOf(playerData, shield->getItemType());
 
  addEquipmentToInventory(weapon, player);
  addEquipmentToInventory(armor, player);
  addEquipmentToInventory(helmet, player);
  addEquipmentToInventory(shield, player);
  for (int i = 0; i < player->getInventory().getSize(); i++) {
    if (playerData[13 + i] != 0) {
      Item* item = createItem(playerData[13 + i]);
      player->getInventory().addItem(item);
    }
  }
  
  return player;
}

Weapon* MasterFactory::createWeapon(int itemType) {
  std::unordered_map<std::string, float>& weaponStats =
      config.getValuesByItemType(itemType);
  return new Weapon(idGenerator++, itemType, weaponStats["minDmg"],
                    weaponStats["maxDmg"], weaponStats["range"],
                    weaponStats["manaRequired"], config.getItemName(itemType),
                    weaponStats["buyPrice"], weaponStats["sellPrice"]);
}

Armor* MasterFactory::createArmor(int itemType) {
  std::unordered_map<std::string, float>& armorStats =
      config.getValuesByItemType(itemType);
  return new Armor(idGenerator++, itemType, armorStats["minDef"],
                   armorStats["maxDef"], config.getItemName(itemType),
                   armorStats["buyPrice"], armorStats["sellPrice"]);
}

Helmet* MasterFactory::createHelmet(int itemType) {
  std::unordered_map<std::string, float>& helmetStats =
      config.getValuesByItemType(itemType);
  return new Helmet(idGenerator++, itemType, helmetStats["minDef"],
                    helmetStats["maxDef"], config.getItemName(itemType),
                    helmetStats["buyPrice"], helmetStats["sellPrice"]);
}

Shield* MasterFactory::createShield(int itemType) {
  std::unordered_map<std::string, float>& shieldStats =
      config.getValuesByItemType(itemType);
  return new Shield(idGenerator++, itemType, shieldStats["minDef"],
                    shieldStats["maxDef"], config.getItemName(itemType),
                    shieldStats["buyPrice"], shieldStats["sellPrice"]);
}

Item* MasterFactory::createItem(int itemType) {
  if (itemType == POCIONMANA_TYPE) {
    return createManaPotion(itemType);
  } else if (itemType == POCIONHP_TYPE) {
    return createHpPotion(itemType);
  } else if (armors.find(itemType) != armors.end()) {
    return createArmor(itemType);
  } else if (helmets.find(itemType) != helmets.end()) {
    return createHelmet(itemType);
  } else if (shields.find(itemType) != shields.end()) {
    return createShield(itemType);
  } else if (weapons.find(itemType) != weapons.end()) {
    return createWeapon(itemType);
  }
  return nullptr;
}

GoldDrop* MasterFactory::createDroppableGold(int goldAmount) {
  return new GoldDrop(idGenerator++, GOLDDROP_TYPE,
                      config.getItemName(GOLDDROP_TYPE), goldAmount);
}

ManaPotion* MasterFactory::createManaPotion(int itemType) {
  std::unordered_map<std::string, float>& potionStats =
      config.getValuesByItemType(itemType);
  return new ManaPotion(idGenerator++, itemType, config.getItemName(itemType),
                        potionStats["buyPrice"], potionStats["sellPrice"],
                        potionStats["recovery"]);
}

HpPotion* MasterFactory::createHpPotion(int itemType) {
  std::unordered_map<std::string, float>& potionStats =
      config.getValuesByItemType(itemType);
  return new HpPotion(idGenerator++, itemType, config.getItemName(itemType),
                      potionStats["buyPrice"], potionStats["sellPrice"],
                      potionStats["recovery"]);
}

Merchant* MasterFactory::createMerchant(int x, int y) {
  return new Merchant(idGenerator++, x, y, listener, *this);
}

Priest* MasterFactory::createPriest(int x, int y) {
  return new Priest(idGenerator++, x, y, listener, *this);
}

Banker* MasterFactory::createBanker(int x, int y) {
  return new Banker(idGenerator++, x, y, listener, *this, bank);
}

void MasterFactory::rmFirstAppearanceOf(std::vector<uint32_t>& v, uint32_t elem) {
  auto it = std::find(v.begin() + 13, v.end(), elem);
  if(it != v.end()) {
    v.erase(it);
  }
}


void MasterFactory::addEquipmentToInventory(Item* item, PlayerNet* player) {
  if (item->getItemType() != 0) {
    player->getInventory().addItem(item);
  }
}
