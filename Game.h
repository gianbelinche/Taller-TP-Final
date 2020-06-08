#ifndef GAME_H
#define GAME_H

#include <unordered_map>

#include "PlayerTestNet.h"
#include "ProtectedStrQueue.h"
#include "ServerEventHandler.h"
#include "Thread.h"

class Game {
private:
  // Lista de entidades(NPCs, bichos)
  // Lista de jugadores o map
  std::unordered_map<std::string, PlayerTestNet> onlinePlayers;
  ProtectedStrQueue incomingEvents;
  ServerEventHandler handler;
public:
  Game();

  ~Game();

  void run();

  void loop();

  void processInput();
};

#endif
