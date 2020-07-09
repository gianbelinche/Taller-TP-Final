#include "headers/Game.h"

#include <unistd.h>

#include <iostream>

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
    processInput();  // Decodifica y procesa todos los eventos encolados
    update();
    persist++;
    if (persist == PERSIST_TIME_DELAY){
      std::cout << "Persistiendo todos los jugadores \n";
      world.persist();
      persist = 0;
    }
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
