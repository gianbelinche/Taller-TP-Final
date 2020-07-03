#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "Communication/MessageDispatcher.h"
#include "Communication/ProtectedQueue.h"
#include "Communication/ServerReceiver.h"
#include "Communication/ServerSender.h"
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
  ProtectedQueue<std::string>& incomingMessages;
  ProtectedQueue<std::vector<uint32_t>> outgoingMessages;
  MessageDispatcher& dispatcher;

 public:
  ClientHandler(Socket p, Persistor& persist, Map& worldMap,
                std::atomic<uint32_t>& idAssigner,
                ProtectedQueue<std::string>& incoming,
                MessageDispatcher& msgDispatcher);

  ~ClientHandler();

  void run() override;

  bool finished();

  // Devuelve un vector con los datos necesarios para crear al Player
  std::vector<uint32_t> getCredentials();

  void sendMap();

  std::string receiveMsg(uint32_t len);

  void sendMsg(std::string msg);

  void sendState();

  void sendTiles();

  void sendTerrain();

  void sendStructures();
};

#endif  // CLIENTHANDLER_H
