#ifndef SERVERSENDER_H
#define SERVERSENDER_H

#include <cstdint>
#include <string>
#include <utility>
#include <vector>

#include "Thread.h"
#include "ProtectedQueue.h"
#include "Socket.h"
#include "SocketException.h"

class ServerSender : public Thread {
 private:
  Socket& peer;
  ProtectedQueue<std::vector<uint32_t>>& outgoingMessages;  // Default init
 public:
  ServerSender(Socket& p, ProtectedQueue<std::vector<uint32_t>>& outgoing);

  ~ServerSender();

  void run() override;

  std::string encodeEvent(std::vector<uint32_t> event);

  void sendEvent(std::string event);
};

#endif  // SERVERSENDER_H
