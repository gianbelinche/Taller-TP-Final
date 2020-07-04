#include "../headers/ServerReceiver.h"

#include <iostream>
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
    std::cout << "El largo: " << msgLen << std::endl;
    std::string msg = std::move(receiveMsg(msgLen));
    std::cout << "msg: " << msg << std::endl;
    incomingEvents.push(std::move(msg));
  }
}

std::string ServerReceiver::receiveMsg(uint32_t len) {
  std::vector<char> msgBuff(len);
  std::cout << "bytes recibidos msg: " << peer.recv(msgBuff.data(), len) << std::endl;
  std::string ss(msgBuff.begin(), msgBuff.end());
  return ss;
}

uint32_t ServerReceiver::receiveLen() {
  char lenBuff[4];
  std::cout << "bytes recibidos len: " << peer.recv(lenBuff, sizeof(uint32_t)) << std::endl;
  uint32_t len = *((uint32_t*)lenBuff);
  return htonl(len);
}
