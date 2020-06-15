#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <unordered_map>
#include <vector>

#include "Entity.h"
#include "PlayerNet.h"

#define TILE_SIZE 32

class GameState
{
private:
  std::vector<std::vector<int>> colisionMap;
  std::unordered_map<int, PlayerNet*> players;
  std::unordered_map<int, Entity*> monsters; 
public:
  GameState();

  ~GameState();

  PlayerNet* getPlayer(int id);

  bool isValidPosition(int x, int y);

  void playerMoved(int id);
};

#endif // GAMESTATE_H
