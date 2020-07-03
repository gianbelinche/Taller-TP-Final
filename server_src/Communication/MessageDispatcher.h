#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <string>

#include "ProtectedQueue.h"

class MessageDispatcher {
private:
  std::unordered_map<uint32_t, ProtectedQueue<std::vector<uint32_t>>> players;
public:
  MessageDispatcher();

  ~MessageDispatcher();

  void broadcastMessage(std::vector<uint32_t> event);

  void sendMessage(int destinyId, std::vector<uint32_t> event);
};

#endif // MESSAGEDISPATCHER_H
