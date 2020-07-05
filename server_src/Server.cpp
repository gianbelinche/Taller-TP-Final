#include "headers/Server.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>
#include <string>

#include "headers/MessageDispatcher.h"
#include "headers/ProtectedQueue.h"
#include "headers/ServerEventHandler.h"
#include "headers/ServerEventListener.h"
#include "headers/Game.h"
#include "headers/GameState.h"
#include "headers/Map.h"
#include "headers/Persistor.h"
#include "headers/ServerProtocol.h"

Server::Server(const char* port, Configuration& configuration)
    : clientAcceptor(port),
      config(configuration),
      keepAccepting(true) {}

Server::~Server() {}

void Server::run() {
  std::atomic<uint32_t> idAssigner{1};
  Map map(MAP_PATH);

  MessageDispatcher dispatcher;
  ServerEventListener listener(dispatcher);
  GameState world(map.getCollisionMap(), config.getFPS(), listener);
  ServerEventHandler handler(world, listener);
  ServerProtocol protocol(handler);

  ProtectedQueue<std::string> incomingMessages;
  Game game(world, idAssigner, incomingMessages, protocol);
  Persistor persistor;

  // game.init()  // quizas hay que hacer algo asi
  game.start();  // Lanza el hilo principal del juego

  while (keepAccepting) {
    Socket peer = std::move(clientAcceptor.accept());
    ClientHandler* cli =
        new ClientHandler(std::move(peer), persistor, map, idAssigner,
                          incomingMessages, dispatcher, world, listener, config);

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
