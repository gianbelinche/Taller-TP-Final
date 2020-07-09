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

Server::Server(const char* port, Configuration& configuration)
    : clientAcceptor(port), config(configuration), keepAccepting(true) {}

Server::~Server() {}

void Server::run() {
  std::atomic<uint32_t> idAssigner{1};
  Map map(MAP_PATH);

  MessageDispatcher dispatcher;
  ServerEventListener listener(dispatcher);
  MasterFactory factory(idAssigner, config, listener);
  GameState world(map.getCollisionMap(), map.getCitiesMap(), config.getFPS(), 
                  listener, factory, config);
  ServerEventHandler handler(world, listener, config);
  ServerProtocol protocol(handler);

  ProtectedQueue<std::string> incomingMessages;
  Game game(world, idAssigner, incomingMessages, protocol);
  Persistor persistor;

  world.init();
  game.start();  // Lanza el hilo principal del juego

  while (keepAccepting) {
    Socket peer = std::move(clientAcceptor.accept());
    ClientHandler* cli = new ClientHandler(std::move(peer), persistor, map,
                                           idAssigner, incomingMessages,
                                           dispatcher, world, listener, config);

    clients.push_back(cli);
    cli->start();
    releaseDeadClients();
  }
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
