#include "../headers/MessageDispatcher.h"

MessageDispatcher::MessageDispatcher() {}

MessageDispatcher::~MessageDispatcher() {}

void MessageDispatcher::broadcastMessage(std::vector<uint32_t> event) {
  std::unique_lock<std::mutex> l(m);
  for (auto& it : players) {
    if (it.second->isEnabled()) {
      it.second->push(event);
    }
  }
}

void MessageDispatcher::sendMessage(int destinyId,
                                    std::vector<uint32_t> event) {
  std::unique_lock<std::mutex> l(m);
  if (players.find(destinyId) != players.end()) {  // El jugador se desconecto?
    players[destinyId]->push(event);
  }
}

void MessageDispatcher::addPlayerQueue(
    uint32_t id, ProtectedQueue<std::vector<uint32_t>>* q) {
  std::unique_lock<std::mutex> l(m);
  players.insert(
      std::pair<uint32_t, ProtectedQueue<std::vector<uint32_t>>*>(id, q));
}
