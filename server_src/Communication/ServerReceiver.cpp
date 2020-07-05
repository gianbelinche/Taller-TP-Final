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
  try {
    while (keepRunning) {
      uint32_t msgLen = receiveLen();
      if (msgLen == 0) {
        continue;
      }
      std::string msg = std::move(receiveMsg(msgLen));
      incomingEvents.push(std::move(msg));
    }
  } catch (const SocketException& e) {
    std::cout << "Atrapo la excepcion" << std::endl;
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
  if (peer.recv(lenBuff, sizeof(uint32_t)) == 0) {
    return 0;
  } 
  uint32_t len = *((uint32_t*)lenBuff);
  return htonl(len);
}


void ServerReceiver::stop() {
  keepRunning = false;
}
