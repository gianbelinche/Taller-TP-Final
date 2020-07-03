#ifndef SERVERRECEIVER_H
#define SERVERRECEIVER_H

#include <atomic>
#include <cstdint>
#include <string>

#include "Thread.h"
#include "ProtectedQueue.h"
#include "Socket.h"

class ServerReceiver : public Thread {
 private:
  Socket& peer;
  ProtectedQueue<std::string>& incomingEvents;
  std::atomic<bool> keepRunning;

 public:
  ServerReceiver(Socket& peer, ProtectedQueue<std::string>& incoming);

  ~ServerReceiver();

  void run() override;

  std::string receiveMsg(uint32_t len);

  uint32_t receiveLen();
};

#endif  // SERVERRECEIVER_H
