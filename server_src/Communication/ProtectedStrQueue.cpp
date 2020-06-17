#include <utility>

#include "ProtectedStrQueue.h"

ProtectedStrQueue::ProtectedStrQueue() {}

ProtectedStrQueue::~ProtectedStrQueue() {}

void ProtectedStrQueue::push(std::string s) {
  std::unique_lock<std::mutex> l(m);
  q.push(std::move(s));
}

// Si se va a usar para algo ver de mandarle el mutex
std::string ProtectedStrQueue::pop() {
  std::string frontElement = q.front();
  q.pop();
  return frontElement;
}

void ProtectedStrQueue::emptyQueue(std::vector<std::string> &events) {
  std::unique_lock<std::mutex> l(m);
  while (!q.empty()) {
    events.push_back(std::move(q.front()));
    q.pop();
  }
}