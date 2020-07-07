#include "../headers/MasterFactory.h"

MasterFactory::MasterFactory(std::atomic<uint32_t>& idCounter,
                             Configuration& configuration,
                             ServerEventListener& eventListener)
    : idGenerator(idCounter),
      config(configuration),
      listener(eventListener),
      goblin(config.getValues(GOBLIN)["hp"], config.getValues(GOBLIN)["damage"],
             config.getValues(GOBLIN)["level"], 2,
             config.getValues(GOBLIN)["velocity"],
             config.getValues(GOBLIN)["attackRange"],
             config.getValues(GOBLIN)["pursuitDistance"]),
      spider(config.getValues(SPIDER)["hp"], config.getValues(SPIDER)["damage"],
             config.getValues(SPIDER)["level"], 0,
             config.getValues(SPIDER)["velocity"],
             config.getValues(SPIDER)["attackRange"],
             config.getValues(SPIDER)["pursuitDistance"]),
      skeleton(config.getValues(SKELETON)["hp"],
               config.getValues(SKELETON)["damage"],
               config.getValues(SKELETON)["level"], 1,
               config.getValues(SKELETON)["velocity"],
               config.getValues(SKELETON)["attackRange"],
               config.getValues(SKELETON)["pursuitDistance"]),
      zombie(config.getValues(ZOMBIE)["hp"], config.getValues(ZOMBIE)["damage"],
             config.getValues(ZOMBIE)["level"], 3,
             config.getValues(ZOMBIE)["velocity"],
             config.getValues(ZOMBIE)["attackRange"],
             config.getValues(ZOMBIE)["pursuitDistance"]),
      human(HUMAN_ID, config.getValues(HUMAN)["hpFactor"],
            config.getValues(HUMAN)["recoveryFactor"],
            config.getValues(HUMAN)["manaFactor"],
            config.getValues(HUMAN)["constitution"],
            config.getValues(HUMAN)["strength"],
            config.getValues(HUMAN)["intelligence"],
            config.getValues(HUMAN)["agility"]),  
      elf(ELF_ID, config.getValues(ELF)["hpFactor"],
          config.getValues(ELF)["recoveryFactor"],
          config.getValues(ELF)["manaFactor"],
          config.getValues(ELF)["constitution"],
          config.getValues(ELF)["strength"],
          config.getValues(ELF)["intelligence"],
          config.getValues(ELF)["agility"]),
      dwarf(DWARF_ID, config.getValues(DWARF)["hpFactor"],
            config.getValues(DWARF)["recoveryFactor"],
            config.getValues(DWARF)["manaFactor"],
            config.getValues(DWARF)["constitution"],
            config.getValues(DWARF)["strength"],
            config.getValues(DWARF)["intelligence"],
            config.getValues(DWARF)["agility"]),
      gnome(GNOME_ID, config.getValues(GNOME)["hpFactor"],
            config.getValues(GNOME)["recoveryFactor"],
            config.getValues(GNOME)["manaFactor"],
            config.getValues(GNOME)["constitution"],
            config.getValues(GNOME)["strength"],
            config.getValues(GNOME)["intelligence"],
            config.getValues(GNOME)["agility"]),
      warrior(WARRIOR_ID, config.getValues(WARRIOR)["hpFactor"],
              config.getValues(WARRIOR)["manaFactor"],
              config.getValues(WARRIOR)["meditFac"],
              config.getValues(WARRIOR)["strengthFactor"],
              config.getValues(WARRIOR)["constitutionFactor"],
              config.getValues(WARRIOR)["intelligenceFactor"],
              config.getValues(WARRIOR)["agilityFactor"]),
      wizard(WIZARD_ID, config.getValues(WIZARD)["hpFactor"],
             config.getValues(WIZARD)["manaFactor"],
             config.getValues(WIZARD)["meditFac"],
             config.getValues(WIZARD)["strengthFactor"],
             config.getValues(WIZARD)["constitutionFactor"],
             config.getValues(WIZARD)["intelligenceFactor"],
             config.getValues(WIZARD)["agilityFactor"]),
      cleric(CLERIC_ID, config.getValues(CLERIC)["hpFactor"],
             config.getValues(CLERIC)["manaFactor"],
             config.getValues(CLERIC)["meditFac"],
             config.getValues(CLERIC)["strengthFactor"],
             config.getValues(CLERIC)["constitutionFactor"],
             config.getValues(CLERIC)["intelligenceFactor"],
             config.getValues(CLERIC)["agilityFactor"]),
      paladin(PALADIN_ID, config.getValues(PALADIN)["hpFactor"],
              config.getValues(PALADIN)["manaFactor"],
              config.getValues(PALADIN)["meditFac"],
              config.getValues(PALADIN)["strengthFactor"],
              config.getValues(PALADIN)["constitutionFactor"],
              config.getValues(PALADIN)["intelligenceFactor"],
              config.getValues(PALADIN)["agilityFactor"]) {
  races[HUMAN_ID] = &human;
  races[ELF_ID] = &elf;
  races[DWARF_ID] = &dwarf;
  races[GNOME_ID] = &gnome;

  classes[WARRIOR_ID] = &warrior;
  classes[WIZARD_ID] = &wizard;
  classes[CLERIC_ID] = &cleric;
  classes[PALADIN_ID] = &paladin;
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
  
  PlayerNet* player = new PlayerNet(
      x, y, id, world, 6, exp, level, gold, createWeapon(playerData[9]),
      createArmor(playerData[11]), createHelmet(playerData[10]),
      createShield(playerData[12]), state, playerClass, playerRace, listener);

  for (int i = 0; i < player->getInventory().getSize();i++){
    if (playerData[13+i] != 0){
      Item* item = createItem(playerData[13+i]);
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
                    config.getItemName(itemType), weaponStats["buyPrice"],
                    weaponStats["sellPrice"]);
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
