#ifndef MASTERFACTORY_H
#define MASTERFACTORY_H

#include <atomic>
#include <unordered_map>
#include <vector>

#include "Armor.h"
#include "Class.h"
#include "Configuration.h"
#include "GhostState.h"
#include "Helmet.h"
#include "Item.h"
#include "MonsterType.h"
#include "NormalState.h"
#include "PlayerNet.h"
#include "PlayerState.h"
#include "Race.h"
#include "ServerEventListener.h"
#include "Shield.h"
#include "Weapon.h"
#include "Wearable.h"

#define GOBLIN "goblin"
#define SKELETON "skeleton"
#define SPIDER "spider"
#define ZOMBIE "zombie"

#define HUMAN "human"
#define ELF "elf"
#define DWARF "dwarf"
#define GNOME "gnome"

#define WARRIOR "warrior"
#define WIZARD "wizard"
#define CLERIC "cleric"
#define PALADIN "paladin"

#define HUMAN_ID 0
#define ELF_ID 1
#define DWARF_ID 2
#define GNOME_ID 3

#define WARRIOR_ID 0
#define WIZARD_ID 1
#define CLERIC_ID 2
#define PALADIN_ID 3

// Avoid circular dependencies
class GameState; 
class Monster;

class MasterFactory {
 private:
  std::atomic<uint32_t>& idGenerator;
  Configuration& config;
  ServerEventListener& listener;
  MonsterType goblin;
  MonsterType spider;
  MonsterType skeleton;
  MonsterType zombie;
  Race human;
  Race elf;
  Race dwarf;
  Race gnome;
  Class warrior;
  Class wizard;
  Class cleric;
  Class paladin;
  std::unordered_map<uint32_t, Race*> races;
  std::unordered_map<uint32_t, Class*> classes;

 public:
  MasterFactory(std::atomic<uint32_t>& idCounter, Configuration& configuration,
                ServerEventListener& eventListener);

  ~MasterFactory();

  Monster* newGoblin(int x, int y, GameState& world);

  Monster* newSkeleton(int x, int y, GameState& world);

  Monster* newSpider(int x, int y, GameState& world);

  Monster* newZombie(int x, int y, GameState& world);

  PlayerNet* createPlayer(std::vector<uint32_t>& playerData, GameState& world);

  Weapon* createWeapon(int itemType);

  Armor* createArmor(int itemType);

  Helmet* createHelmet(int itemType);

  Shield* createShield(int itemType);
};

#endif  // MASTERFACTORY_H
