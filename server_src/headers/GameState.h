#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <utility>
#include <vector>

#include "Condition.h"
#include "Configuration.h"
#include "Entity.h"
#include "Item.h"
#include "NPC.h"
#include "NormalState.h"
#include "PlayerNet.h"
#include "PlayerState.h"

#define TILE_SIZE 32
#define MAX_AMOUNT_NPC 500

class MasterFactory;
class Monster;

class GameState {
 private:
  Configuration& config;
  std::vector<std::vector<bool>>& colisionMap;
  std::vector<std::vector<bool>>& citiesMap;
  std::unordered_map<int, PlayerNet*> players;
  std::unordered_map<int, Item*> droppedItems;
  std::unordered_map<int, std::pair<int, int>> itemsPositions;
  std::unordered_map<std::string, int> usrToId;
  std::unordered_map<int, std::string> idToUsr;
  std::unordered_map<int, Entity*> entities;  // Jugadores y monstruos
  std::unordered_map<int, NPC*> npcs;
  int framesPerSecond;
  ServerEventListener& listener;
  MasterFactory& factory;
  std::mutex entitiesMapMutex;
  std::mutex usrIdMutex;
  std::mutex idUsrMutex;
  int maxAmountNPC;

 public:
  GameState(std::vector<std::vector<bool>>& collisions,
            std::vector<std::vector<bool>>& cities, int fps,
            ServerEventListener& eventListener, MasterFactory& fac,
            Configuration& configuration);

  ~GameState();

  void init();

  void addEntity(Entity* ent);

  void addPlayer(PlayerNet* player);

  void addUsernameId(std::string user, int id);

  void rmUsrId(std::string user);

  int getIdByUsername(std::string username);

  void addIdUsername(int id, std::string user);

  void rmIdUsr(int id);

  std::string getUsernameById(int id);

  void rmPlayer(int id);

  void rmEntity(int id);

  Entity* getEntity(int id);

  int getFPS();

  PlayerNet* getNearestPlayer(Entity* ent, Condition* cond = nullptr);

  PlayerNet* getPlayer(int id);

  NPC* getNpc(int id);

  bool isValidPosition(int x, int y);

  bool isCityPosition(int x, int y);

  float entitiesDistance(Entity* ent1, Entity* ent2);

  bool playerCanAttack(PlayerNet* player, Entity* ent);

  void addPlayerFromData(std::vector<uint32_t>& playerData);

  void update();

  void sendState(int id);

  bool isNpc(int id);

  bool isPlayer(int id);

  bool isEntitiy(int id);

  void spawnUnParDeMobs();

  void dropItem(Item* item, int x, int y);

  Item* getCloseItem(int x, int y, int range);

  void rmItem(int id);

  void generateDrop(int x, int y);

  std::pair<int, int> generateNewMonsterPosition();

  Monster* generateRandomMonster(int x, int y);

 private:
  void initNPCs();

  void initMobs();
};

#endif  // GAMESTATE_H
