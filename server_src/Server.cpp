#include "headers/Server.h"

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>

#include "headers/Game.h"
#include "headers/GameState.h"
#include "headers/Map.h"
#include "headers/MasterFactory.h"
#include "headers/MessageDispatcher.h"
#include "headers/Persistor.h"
#include "headers/ProtectedQueue.h"
#include "headers/ServerEventHandler.h"
#include "headers/ServerEventListener.h"
#include "headers/ServerProtocol.h"

Server::Server(int port, Configuration& configuration)
    : clientAcceptor(port),
      config(configuration),
      keepAccepting(true),
      idAssigner(1),
      map(MAP_PATH),
      listener(dispatcher),
      factory(idAssigner, config, listener),
      world(map.getCollisionMap(), map.getCitiesMap(), config.getFPS(),
            listener, factory, config, config.getValues("npcsAmount")),
      handler(world, listener, config),
      protocol(handler),
      game(world, idAssigner, incomingMessages, protocol) {}

Server::~Server() {}

void Server::run() {
  world.init();
  game.start();  // Lanza el hilo principal del juego

  try {
    while (keepAccepting) {
      Socket peer = std::move(clientAcceptor.accept());
      ClientHandler* cli = new ClientHandler(
          std::move(peer), persistor, map, idAssigner, incomingMessages,
          dispatcher, world, listener, config);

      clients.push_back(cli);
      cli->start();
      releaseDeadClients();
    }
  } catch (SocketException& e) {
    if (keepAccepting) {
      throw e;
    }
  }
  releaseAllClients();
  game.stop();
  game.join();
}

void Server::stop() {
  keepAccepting = false;
  clientAcceptor.close();
}

void Server::releaseDeadClients() {
  for (std::list<ClientHandler*>::iterator it = clients.begin();
       it != clients.end();) {
    if ((*it)->finished()) {
      (*it)->join();
      delete *it;
      it = clients.erase(it);
    } else {
      ++it;
    }
  }
}

void Server::releaseAllClients() {
  for (std::list<ClientHandler*>::iterator it = clients.begin();
       it != clients.end();) {
    (*it)->join();
    delete *it;
    it = clients.erase(it);
  }
}
