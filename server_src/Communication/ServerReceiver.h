#ifndef SERVERRECEIVER_H
#define SERVERRECEIVER_H

#include <atomic>
#include <cstdint>

#include "../resources/Thread.h"
#include "ProtectedStrQueue.h"
#include "Socket.h"

class ServerReceiver : public Thread {
 private:
  Socket& peer;
  ProtectedStrQueue& incomingEvents;
  std::atomic<bool> keepRunning;

 public:
  ServerReceiver(Socket& peer, ProtectedStrQueue incoming);

  ~ServerReceiver();

  void run() override;

  std::string receiveMsg(uint32_t len);

  uint32_t receiveLen();
};

#endif  // SERVERRECEIVER_H
