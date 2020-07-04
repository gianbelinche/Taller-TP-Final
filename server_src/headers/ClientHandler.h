#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H
#include <atomic>
#include <cstdint>
#include <string>
#include <vector>

#include "Class.h"
#include "GameState.h"
#include "Map.h"
#include "MessageDispatcher.h"
#include "Monster.h"
#include "MonsterType.h"
#include "NormalState.h"
#include "Persistor.h"
#include "PlayerNet.h"
#include "PlayerState.h"
#include "ProtectedQueue.h"
#include "Race.h"
#include "ServerEventListener.h"
#include "ServerReceiver.h"
#include "ServerSender.h"
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
  GameState& world;
  ServerEventListener& listener;

 public:
  ClientHandler(Socket p, Persistor& persist, Map& worldMap,
                std::atomic<uint32_t>& idAssigner,
                ProtectedQueue<std::string>& incoming,
                MessageDispatcher& msgDispatcher, GameState& state,
                ServerEventListener& eventListener);

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

  void sendSuccesfulLogin();

  void sendFailedLogin();

  void sendPlayerCreationNeeded();

  void handleNewPlayer(std::string user);

  std::vector<uint32_t> getSendablePlayerInfo(std::vector<uint32_t>& playerData);
};

#endif  // CLIENTHANDLER_H
