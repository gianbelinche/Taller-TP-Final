#ifndef GAME_H
#define GAME_H

#include <atomic>
#include <unordered_map>
#include <vector>

#include "Entity.h"
// #include "UserMoved.h"
#include "PlayerTestNet.h"
#include "ProtectedStrQueue.h"
#include "ServerEventHandler.h"
#include "Thread.h"

class Game : public Thread {
private:
  // Lista de entidades(NPCs, bichos)
  std::vector<Entity*> entities;
  // Lista de jugadores o map
  std::unordered_map<int, PlayerTestNet> onlinePlayers;
  ProtectedStrQueue incomingEvents;
  // ServerEventHandler handler;
  std::atomic<bool> keep_running;
public:
  Game();

  ~Game();

  void run();

  void loop();

  void processInput();

  void update();

  // Funciones de prueba de momento
  void addPlayer(int id);

  void addEntity();

  void addIncoming(std::string s);
private:
  // De momento un string con la dirección, probablemente cambie
  void movePlayer(std::string &move);
};

#endif
