#include "ServerReceiver.h"

#include "arpa/inet.h"
#include <utility>

ServerReceiver::ServerReceiver(Socket& peer, ProtectedStrQueue incoming)
    : peer(peer), incomingEvents(incoming) {}

ServerReceiver::~ServerReceiver() {}

void ServerReceiver::run() {
  while (keepRunning) {
    uint32_t msgLen = receiveLen();
    std::string msg = std::move(receiveMsg(msgLen));
    incomingEvents.push(std::move(msg));
  }
}

std::string ServerReceiver::receiveMsg(uint32_t len) {
  std::vector<char> msgBuff(len);
  peer.recv(msgBuff.data(), len);
  std::string ss(msgBuff.begin(), msgBuff.end());
  return std::move(ss);
}

uint32_t ServerReceiver::receiveLen() {
  char* lenBuff;
  peer.recv(lenBuff, sizeof(uint32_t));
  uint32_t len = *((uint32_t*)lenBuff);
  return ntohl(len);
}
