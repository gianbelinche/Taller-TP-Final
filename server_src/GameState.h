#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <unordered_map>
#include <vector>

#include "Condition.h"
#include "Entities/Entity.h"
#include "PlayerNet.h"

#define TILE_SIZE 32

class GameState {
 private:
  std::vector<std::vector<int>> colisionMap;
  std::unordered_map<int, PlayerNet*> players;
  std::unordered_map<int, Entity*> entities;  // Jugadores y mosntruos
  int framesPerSecond;

 public:
  GameState(int fps);

  ~GameState();

  PlayerNet* getPlayer(int id);

  Entity* getEntity(int id);

  int getFPS();

  bool isValidPosition(int x, int y);

  PlayerNet* getNearestPlayer(Entity* ent, Condition* cond = nullptr);

  float entitiesDistance(Entity* ent1, Entity* ent2);

  bool playerCanAttack(PlayerNet* player, Entity* ent);

  /* ---------- Eventos ---------- */

  void playerMoved(int id); // Ver si conviene mergearlos en uno solo

  void playerDealtDamage(int id, int damage);

  void playerTookDamage(int id, int damage);

  void monsterMoved(int id); 

  void playerDied(int id);

  void entityDisappear(int id) // Jugadores que se desconectan o mobs que mueren
};

#endif  // GAMESTATE_H
