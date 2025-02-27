#ifndef MESSAGEDISPATCHER_H
#define MESSAGEDISPATCHER_H

#include <cstdint>
#include <unordered_map>
#include <vector>
#include <mutex>
#include <string>

#include "ProtectedQueue.h"

class MessageDispatcher {
private:
  std::unordered_map<uint32_t, ProtectedQueue<std::vector<uint32_t>>*> players;
  std::mutex m;
public:
  MessageDispatcher();

  ~MessageDispatcher();

  void broadcastMessage(std::vector<uint32_t> event);

  void sendMessage(int destinyId, std::vector<uint32_t> event);

  void addPlayerQueue(uint32_t id, ProtectedQueue<std::vector<uint32_t>>* q);

  void playerConnected(uint32_t id);

  void deletePlayerQueue(uint32_t id);
};

#endif // MESSAGEDISPATCHER_H
