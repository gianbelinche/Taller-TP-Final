#include "Server.h"

#include <fstream>
#include <iostream>
#include <unordered_map>
#include <utility>

#include "Communication/MessageDispatcher.h"
#include "Communication/ProtectedQueue.h"
#include "Game.h"
#include "Events/ServerEventHandler.h"
#include "Events/ServerEventListener.h"
#include "resources/GameState.h"
#include "resources/Map.h"
#include "resources/Persistor.h"
#include "resources/ServerProtocol.h"

Server::Server(const char* port, Configuration configuration)
    : clientAcceptor(port),
      config(std::move(configuration)),
      keepAccepting(true) {}

Server::~Server() {}

void Server::run() {
  std::atomic<uint32_t> idAssigner{1};
  Map map(MAP_PATH);
  GameState world(map.getCollisionMap(), 30);

  MessageDispatcher dispatcher;
  ServerEventListener listener(dispatcher);
  ServerEventHandler handler(world, listener);
  ServerProtocol protocol(handler);
  
  ProtectedQueue<std::string> incomingMessages;
  Game game(world, idAssigner, incomingMessages, protocol);
  Persistor persistor;

  // game.init()  // quizas hay que hacer algo asi
  game.start();  // Lanza el hilo principal del juego

  while (keepAccepting) {
    Socket peer = std::move(clientAcceptor.accept());
    ClientHandler* cli = new ClientHandler(std::move(peer), persistor, map,
                                           idAssigner, incomingMessages);

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
