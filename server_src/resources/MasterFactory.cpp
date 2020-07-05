#include "../headers/MasterFactory.h"

MasterFactory::MasterFactory(std::atomic<uint32_t>& idCounter,
                             Configuration& configuration, GameState& gameState,
                             ServerEventListener& eventListener)
    : idGenerator(idCounter),
      config(configuration),
      world(gameState),
      listener(eventListener),
      goblin(config.getValues(GOBLIN)["hp"], config.getValues(GOBLIN)["damage"],
             config.getValues(GOBLIN)["level"]),
      spider(config.getValues(SPIDER)["hp"], config.getValues(SPIDER)["damage"],
             config.getValues(SPIDER)["level"]),
      skeleton(config.getValues(SKELETON)["hp"],
               config.getValues(SKELETON)["damage"],
               config.getValues(SKELETON)["level"]),
      zombie(config.getValues(ZOMBIE)["hp"], config.getValues(ZOMBIE)["damage"],
             config.getValues(ZOMBIE)["level"]),
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

Monster* MasterFactory::newGoblin(int x, int y) {
  return goblin.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newSkeleton(int x, int y) {
  return skeleton.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newSpider(int x, int y) {
  return spider.newMonster(idGenerator++, x, y, world, listener);
}

Monster* MasterFactory::newZombie(int x, int y) {
  return zombie.newMonster(idGenerator++, x, y, world, listener);
}

PlayerNet* MasterFactory::createPlayer(std::vector<uint32_t>& playerData) {
  uint32_t id = playerData[0];
  uint32_t x = playerData[1];
  uint32_t y = playerData[2];
  uint32_t level = playerData[3];
  uint32_t exp = playerData[4];
  Race* playerRace = races[playerData[5]];
  Class* playerClass = classes[playerData[6]];
  uint32_t gold = playerData[7];
}
