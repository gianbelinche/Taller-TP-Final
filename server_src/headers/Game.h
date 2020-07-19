#ifndef GAME_H
#define GAME_H

#include <atomic>
#include <string>
#include <unordered_map>
#include <vector>

#include "ProtectedQueue.h"
#include "Entity.h"
#include "ServerEventHandler.h"
#include "GameState.h"
#include "Thread.h"
#include "ServerProtocol.h"

class Game : public Thread {
 private:
  GameState& world;
  std::atomic<bool> keep_running;
  std::atomic<uint32_t>& idAssigner;
  ProtectedQueue<std::string>& incomingEvents;
  ServerProtocol& protocol;
  int persist;

 public:
  Game(GameState& world, std::atomic<uint32_t>& idGenerator,
       ProtectedQueue<std::string>& incoming, ServerProtocol& serverProtocol);

  ~Game();

  void run();

  void loop();

  void processInput();

  void update();

 private:
  void movePlayer(std::string& move);
};

#endif
