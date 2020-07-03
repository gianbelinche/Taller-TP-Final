#include "MessageDispatcher.h"

MessageDispatcher::MessageDispatcher() {}

MessageDispatcher::~MessageDispatcher() {}

void MessageDispatcher::broadcastMessage(std::vector<uint32_t> event) {
  for (auto &it : players) {
    if (it.second.isEnabled()) {
      it.second.push(event);
    }
  }
}

void MessageDispatcher::sendMessage(int destinyId,
                                    std::vector<uint32_t> event) {
  if (players.find() != players.end()) {  // Sino el jugador que se desconecto
    players[destinyId].push(event);
  }
}
