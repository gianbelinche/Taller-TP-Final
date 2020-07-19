#include "headers/Game.h"

#include <unistd.h>

#include <iostream>
#include <chrono>

#define PERSIST_TIME_DELAY 300  //9 segundos aproximadamente

Game::Game(GameState &world, std::atomic<uint32_t> &idGenerator,
           ProtectedQueue<std::string> &incoming,
           ServerProtocol &serverProtocol)
    : world(world),
      keep_running(true),
      idAssigner(idGenerator),
      incomingEvents(incoming),
      protocol(serverProtocol),
      persist(0) {}

Game::~Game() {}

void Game::run() { loop(); }

void Game::loop() {
  while (keep_running) {
    auto start = std::chrono::steady_clock::now();
    processInput();
    update();
    persist++;
    if (persist == PERSIST_TIME_DELAY){
      world.persist();
      persist = 0;
    }
    auto end = std::chrono::steady_clock::now();
    int time = std::chrono::duration<double, std::micro>(end-start).count();
    if (time < 30000) usleep(30000 - time);  // Algo mas de 30 fps
  }
}

void Game::processInput() {
  std::vector<std::string> packedEvents;
  incomingEvents.emptyQueue(packedEvents);
  for (auto &ev : packedEvents) {
    protocol.decode(ev);
  }
}

void Game::update() { world.update(); }
