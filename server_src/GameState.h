#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <unordered_map>
#include <vector>

#include "Entity.h"
#include "PlayerNet.h"

class GameState
{
private:
  std::vector<std::vector<int>> colisionMap;
  std::unordered_map<int, PlayerNet*> players;
  std::unordered_map<int, Entity*> monsters; 
public:
  GameState(/* args */);
  ~GameState();
};

#endif // GAMESTATE_H
