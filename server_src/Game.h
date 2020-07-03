#ifndef GAME_H
#define GAME_H

#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>

#include "Communication/ProtectedQueue.h"
#include "Entities/Entity.h"
#include "Events/ServerEventHandler.h"
#include "resources/GameState.h"
#include "resources/Thread.h"
#include "resources/ServerProtocol.h"

class Game : public Thread {
 private:
  GameState& world;
  std::atomic<bool> keep_running;
  std::atomic<uint32_t>& idAssigner;
  ProtectedQueue<std::string>& incomingEvents;
  ServerProtocol& protocol;

 public:
  Game(GameState& world, std::atomic<uint32_t>& idGenerator,
       ProtectedQueue<std::string>& incoming, ServerProtocol& serverProtocol);

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
