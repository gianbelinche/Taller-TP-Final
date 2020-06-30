#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <list>
#include <string>
#include <unordered_map>

#include "config/Configuration.h"
#include "resources/Acceptor.h"
#include "resources/ClientHandler.h"
#include "resources/Thread.h"

#define MAP_PATH "../map.json"

class Server : public Thread {
 private:
  Acceptor clientAcceptor;
  Configuration config;
  std::list<ClientHandler*> clients;  // efficient erase
  std::atomic<bool> keepAccepting;

 public:
  Server(const char* port, Configuration configuration);

  ~Server();

  void run() override;

  void loadMap(const char* mapPath);

  void releaseDeadClients();

  void releaseAllClients();
};

#endif  // SERVER_H
