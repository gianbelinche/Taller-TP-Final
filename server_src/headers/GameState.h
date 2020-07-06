#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdint>
#include <mutex>
#include <unordered_map>
#include <vector>

#include "Condition.h"
#include "Entity.h"
#include "NormalState.h"
#include "NPC.h"
#include "PlayerNet.h"
#include "PlayerState.h"
#include "MasterFactory.h"

#define TILE_SIZE 32

class GameState {
 private:
  std::vector<std::vector<bool>> colisionMap;
  std::unordered_map<int, PlayerNet*> players;
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

 public:
  GameState(std::vector<std::vector<bool>>& collisions, int fps,
            ServerEventListener& eventListener, MasterFactory& fac);

  ~GameState();

  void addEntity(Entity* ent);

  void addPlayer(PlayerNet* player);

  void addUsernameId(std::string user, int id);

  void rmUsrId(std::string user);

  int getIdByUsername(std::string username);

  void addIdUsername(int id, std::string user);

  void rmIdUsr(int id);

  std::string getUsernameById(int id);

  void rmPlayer(int id);

  Entity* getEntity(int id);

  int getFPS();

  PlayerNet* getNearestPlayer(Entity* ent, Condition* cond = nullptr);

  PlayerNet* getPlayer(int id);

  NPC* getNpc(int id);

  bool isValidPosition(int x, int y);

  float entitiesDistance(Entity* ent1, Entity* ent2);

  bool playerCanAttack(PlayerNet* player, Entity* ent);

  void addPlayerFromData(std::vector<uint32_t>& playerData);

  void update();

  void sendState(int id);

  bool isNpc(int id);

  void spawnUnParDeMobs();
};

#endif  // GAMESTATE_H
