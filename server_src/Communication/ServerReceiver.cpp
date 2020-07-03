#include "../headers/ServerReceiver.h"

#include <string>
#include <utility>

#include "arpa/inet.h"

ServerReceiver::ServerReceiver(Socket& peer,
                               ProtectedQueue<std::string>& incoming)
    : peer(peer), incomingEvents(incoming), keepRunning(true) {}

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
  return ss;
}

uint32_t ServerReceiver::receiveLen() {
  char lenBuff[4];
  peer.recv(lenBuff, sizeof(uint32_t));
  uint32_t len = *((uint32_t*)lenBuff);
  return ntohl(len);
}
