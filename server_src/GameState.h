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
  std::unordered_map<int, Entity*> entities; // Jugadores y mosntruos
  int framesPerSecond;
public:
  GameState(int fps);

  ~GameState();

  PlayerNet* getPlayer(int id);

  Entity* getEntity(int id);

  int getFPS();

  bool isValidPosition(int x, int y);

  PlayerNet* getNearestPlayer(Entity &ent, Condition* cond = nullptr);

  float entitiesDistance(Entity &ent1, Entity &ent2);

  void playerMoved(int id);

  void monsterMoved(int id);
};

#endif // GAMESTATE_H
