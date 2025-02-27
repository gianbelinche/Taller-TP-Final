#include "../headers/ServerSender.h"

#include <iostream>
#include <msgpack.hpp>
#include <sstream>

#include "../headers/ClosedQueueException.h"

ServerSender::ServerSender(Socket& p,
                           ProtectedQueue<std::vector<uint32_t>>& outgoing)
    : peer(p), outgoingMessages(outgoing) {}

ServerSender::~ServerSender() {}

void ServerSender::run() {
  try {
    while (!outgoingMessages.isClosed() || !outgoingMessages.empty()) {
      std::vector<uint32_t> event = outgoingMessages.pop();
      std::string encodedEvent = std::move(encodeEvent(event));
      sendEvent(std::move(encodedEvent));
    }
  } catch (const ClosedQueueException& e) {

  } catch (const SocketException& s) {
  }
}

std::string ServerSender::encodeEvent(std::vector<uint32_t> event) {
  std::stringstream eventBuffer;
  msgpack::pack(eventBuffer, event);
  return std::move(eventBuffer.str());
}

void ServerSender::sendEvent(std::string event) {
  uint32_t len = event.size();
  len = htonl(len);
  // Mando largo
  peer.send((char*)&len, sizeof(uint32_t));
  // Mando el paquete
  peer.send(event.data(), event.size());
}
