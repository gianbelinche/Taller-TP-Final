#include "Server.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>

#include "Game.h"
#include "resources/GameState.h"
#include "resources/Map.h"
#include "resources/Persistor.h"

Server::Server(const char* port, Configuration configuration)
    : clientAcceptor(port),
      config(std::move(configuration)),
      keepAccepting(true) {}

Server::~Server() {}

void Server::run() {
  Map map(MAP_PATH);
  GameState world(map.getCollisionMap(), 30);
  Game game(world);
  Persistor persistor;
  game.run(); // Lanza el hilo principal del juego

  while (keepAccepting) { 
    Socket peer = std::move(clientAcceptor.accept());
    ClientHandler* cli = new ClientHandler(std::move(peer), persistor);
  }
}
