#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <list>
#include <string>
#include <unordered_map>

#include "Configuration.h"
#include "Game.h"
#include "Acceptor.h"
#include "ClientHandler.h"
#include "MasterFactory.h"
#include "ServerEventHandler.h"
#include "ServerProtocol.h"


#include "Thread.h"

#define MAP_PATH "media/json/map.json"

class Server : public Thread {
 private:
  Acceptor clientAcceptor;
  Configuration& config;
  std::list<ClientHandler*> clients;  // efficient erase
  std::atomic<bool> keepAccepting;
  std::atomic<uint32_t> idAssigner;
  Map map;
  MessageDispatcher dispatcher;
  ServerEventListener listener;
  MasterFactory factory;
  GameState world;
  ServerEventHandler handler;
  ServerProtocol protocol;
  ProtectedQueue<std::string> incomingMessages;
  Game game;
  Persistor persistor;

 public:
  Server(int port, Configuration& configuration);

  ~Server();

  void run() override;

  void stop();

  void loadMap(const char* mapPath);

  void releaseDeadClients();

  void releaseAllClients();
};

#endif  // SERVER_H
