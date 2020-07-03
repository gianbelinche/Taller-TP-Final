#include "headers/Game.h"

#include <unistd.h>

#include <iostream>

Game::Game(GameState &world, std::atomic<uint32_t> &idGenerator,
           ProtectedQueue<std::string> &incoming,
           ServerProtocol &serverProtocol)
    : world(world),
      keep_running(true),
      idAssigner(idGenerator),
      incomingEvents(incoming),
      protocol(serverProtocol) {}

Game::~Game() {}

void Game::run() { loop(); }

void Game::loop() {
  while (keep_running) {
    processInput();  // Decodifica y procesa todos los eventos encolados
    update();
    usleep(30000);  // Algo mas de 30 fps
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