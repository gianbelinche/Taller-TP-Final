#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "Map.h"
#include "Persistor.h"
#include "Socket.h"
#include "Thread.h"

class ClientHandler : public Thread {
 private:
  Socket peer;
  Persistor& persistor;
  std::atomic<bool> online;
  Map& map;
  std::atomic<uint32_t>& idGenerator;

 public:
  ClientHandler(Socket p, Persistor& persist, Map& worldMap,
                std::atomic<uint32_t>& idAssigner);

  ~ClientHandler();

  void run() override;

  bool finished();

  // Devuelve un vector con los datos necesarios para crear al Player
  std::vector<uint32_t> getCredentials();

  void sendMap();

  void sendMsg(std::string msg);

  void sendState();
};

#endif // CLIENTHANDLER_H
