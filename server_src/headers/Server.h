#ifndef SERVER_H
#define SERVER_H

#include <atomic>
#include <list>
#include <string>
#include <unordered_map>

#include "Configuration.h"
#include "Acceptor.h"
#include "ClientHandler.h"
#include "Thread.h"

#define MAP_PATH "media/json/map.json"

class Server : public Thread {
 private:
  Acceptor clientAcceptor;
  Configuration& config;
  std::list<ClientHandler*> clients;  // efficient erase
  std::atomic<bool> keepAccepting;

 public:
  Server(const char* port, Configuration& configuration);

  ~Server();

  void run() override;

  void loadMap(const char* mapPath);

  void releaseDeadClients();

  void releaseAllClients();
};

#endif  // SERVER_H
