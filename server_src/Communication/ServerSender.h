#ifndef SERVERSENDER_H
#define SERVERSENDER_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "../resources/Thread.h"
#include "ProtectedQueue.h"
#include "Socket.h"

class ServerSender : public Thread {
 private:
  Socket& peer;
  ProtectedQueue<std::vector<uint32_t>> outgoingMessages;  // Default init
 public:
  ServerSender(Socket& p);

  ~ServerSender();

  void run() override;

  std::string encodeEvent(std::vector<uint32_t> event);

  void sendEvent(std::string event);
};

#endif  // SERVERSENDER_H
