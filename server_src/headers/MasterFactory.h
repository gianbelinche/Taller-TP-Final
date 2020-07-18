#ifndef MASTERFACTORY_H
#define MASTERFACTORY_H

#include <algorithm>
#include <atomic>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "Armor.h"
#include "Bank.h"
#include "Banker.h"
#include "Class.h"
#include "Configuration.h"
#include "GhostState.h"
#include "GoldDrop.h"
#include "Helmet.h"
#include "HpPotion.h"
#include "Item.h"
#include "ManaPotion.h"
#include "Merchant.h"
#include "MonsterType.h"
#include "NormalState.h"
#include "PlayerNet.h"
#include "PlayerState.h"
#include "Priest.h"
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

enum itemsType {
  NOTHING_TYPE,
  ESPADA_TYPE,
  HACHA_TYPE,
  MARTILLO_TYPE,
  VARAFRESNO_TYPE,
  FLAUTAELFICA_TYPE,
  BACULONUDOSO_TYPE,
  BACULOENGARZADO_TYPE,
  ARCOSIMPLE_TYPE,
  ARCOCOMPUESTO_TYPE,
  ARMADURACUERO_TYPE,
  ARMADURAPLACAS_TYPE,
  TUNICAAZUL_TYPE,
  CAPUCHA_TYPE,
  CASCOHIERRO_TYPE,
  ESCUDOTORTUGA_TYPE,
  ESCUDOHIERRO_TYPE,
  SOMBREROMAGICO_TYPE,
  POCIONMANA_TYPE,
  POCIONHP_TYPE,
  GOLDDROP_TYPE
};

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
  Bank bank;

  // Unordered sets para busqueda O(1)
  std::unordered_set<int> armors = {ARMADURACUERO_TYPE, ARMADURAPLACAS_TYPE,
                                    TUNICAAZUL_TYPE};
  std::unordered_set<int> shields = {ESCUDOHIERRO_TYPE, ESCUDOTORTUGA_TYPE};
  std::unordered_set<int> helmets = {CASCOHIERRO_TYPE, CAPUCHA_TYPE,
                                     SOMBREROMAGICO_TYPE};
  std::unordered_set<int> weapons = {
      ESPADA_TYPE,       HACHA_TYPE,        MARTILLO_TYPE,
      VARAFRESNO_TYPE,   FLAUTAELFICA_TYPE, BACULOENGARZADO_TYPE,
      BACULONUDOSO_TYPE, ARCOSIMPLE_TYPE,   ARCOCOMPUESTO_TYPE};
  std::unordered_set<int> potions = {POCIONHP_TYPE, POCIONMANA_TYPE};

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

  Item* createItem(int itemType);

  GoldDrop* createDroppableGold(int goldAmount);

  ManaPotion* createManaPotion(int itemType);

  HpPotion* createHpPotion(int itemType);

  Merchant* createMerchant(int x, int y);

  Priest* createPriest(int x, int y);

  Banker* createBanker(int x, int y);

  void rmFirstAppearanceOf(std::vector<uint32_t>& v, uint32_t elem);

  void addEquipmentToInventory(Item* item, PlayerNet* player);
};
#endif  // MASTERFACTORY_H
