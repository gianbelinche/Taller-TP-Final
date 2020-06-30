#ifndef GAME_H
#define GAME_H

#include <atomic>
#include <unordered_map>
#include <vector>

#include "Communication/ProtectedStrQueue.h"
#include "Entities/Entity.h"
#include "resources/GameState.h"
#include "resources/ServerEventHandler.h"
#include "resources/Thread.h"

class Game : public Thread {
 private:
  GameState& world;
  std::unordered_map<int, Entity*> entities;
  std::unordered_map<int, PlayerNet> onlinePlayers;
  ProtectedStrQueue incomingEvents;
  ServerEventHandler handler;
  std::atomic<bool> keep_running;

 public:
  Game(GameState& world);

  ~Game();

  void run();

  void loop();

  void processInput();

  void update();

  // Funciones de prueba de momento
  void addPlayer(int id);

  void addEntity(Entity* ent);

  void addIncoming(std::string s);

  // TESTING
  ServerEventHandler& getServ();

 private:
  // De momento un string con la dirección, probablemente cambie
  void movePlayer(std::string& move);
};

#endif
