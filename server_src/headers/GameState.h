#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <cstdint>
#include <unordered_map>
#include <vector>

#include "Condition.h"
#include "Entity.h"
#include "NormalState.h"
#include "PlayerNet.h"
#include "PlayerState.h"
#include "MasterFactory.h"

#define TILE_SIZE 32

class GameState {
 private:
  std::vector<std::vector<bool>> colisionMap;
  std::unordered_map<int, PlayerNet*> players;
  std::unordered_map<int, Entity*> entities;  // Jugadores y monstruos
  int framesPerSecond;
  ServerEventListener& listener;
  MasterFactory& factory;

 public:
  GameState(std::vector<std::vector<bool>>& collisions, int fps,
            ServerEventListener& eventListener, MasterFactory& fac);

  ~GameState();

  void addEntity(Entity* ent);

  void addPlayer(PlayerNet* player);

  Entity* getEntity(int id);

  int getFPS();

  PlayerNet* getNearestPlayer(Entity* ent, Condition* cond = nullptr);

  PlayerNet* getPlayer(int id);

  bool isValidPosition(int x, int y);

  float entitiesDistance(Entity* ent1, Entity* ent2);

  bool playerCanAttack(PlayerNet* player, Entity* ent);

  void addPlayerFromData(std::vector<uint32_t>& playerData);

  void update();

  void sendState(int id);

  /* ---------- Eventos ---------- */

  void playerExpGain(int id, int gain);

  void playerLeveledUp(int id);

  void playerMoved(int id,
                   char direction);  // Ver si conviene mergearlos en uno solo

  void playerDealtDamage(int id, int damage);

  void playerTookDamage(int id, int damage);

  void monsterMoved(int id);

  void playerDied(int id);

  // Jugadores que se desconectan o mobs que mueren
  void entityDisappear(int id);

  void spawnUnParDeMobs();
};

#endif  // GAMESTATE_H
