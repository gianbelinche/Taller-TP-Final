#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <unordered_map>
#include <vector>

#include "Condition.h"
#include "Entities/Entity.h"
#include "Entities/PlayerNet.h"

#define TILE_SIZE 32

class GameState {
 private:
  std::vector<std::vector<bool>> colisionMap;
  std::unordered_map<int, PlayerNet*> players;
  std::unordered_map<int, Entity*> entities;  // Jugadores y monstruos
  int framesPerSecond;

 public:
  GameState(std::vector<std::vector<bool>> collisions, int fps);

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

  /* ---------- Eventos ---------- */

  void playerExpGain(int id, int gain);

  void playerLeveledUp(int id);

  void playerMoved(int id, char direction);  // Ver si conviene mergearlos en uno solo

  void playerDealtDamage(int id, int damage);

  void playerTookDamage(int id, int damage);

  void monsterMoved(int id);

  void playerDied(int id);

  // Jugadores que se desconectan o mobs que mueren
  void entityDisappear(int id);
};

#endif  // GAMESTATE_H
