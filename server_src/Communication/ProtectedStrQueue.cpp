#include "ProtectedStrQueue.h"

#include <utility>

#include "ClosedQueueException.h"

ProtectedStrQueue::ProtectedStrQueue() {}

ProtectedStrQueue::~ProtectedStrQueue() {}

void ProtectedStrQueue::close() {
  std::unique_lock<std::mutex> l(m);
  closed = true;
  cv.notify_all();
}

void ProtectedStrQueue::push(std::string s) {
  std::unique_lock<std::mutex> l(m);
  q.push(std::move(s));
  cv.notify_all();  // O one, no cambia nada en nuestro caso, solo va a haber 1
                    // en espera
}

std::string ProtectedStrQueue::pop() {
  std::unique_lock<std::mutex> l(m);
  while (q.empty()) {
    if (closed) {
      throw ClosedQueueException("La cola esta cerrada");
    }
    cv.wait(l);
  }
  std::string poppedMsg = q.front();
  q.pop();
  return std::move(poppedMsg);
}

void ProtectedStrQueue::emptyQueue(std::vector<std::string> &events) {
  std::unique_lock<std::mutex> l(m);
  while (!q.empty()) {
    events.push_back(std::move(q.front()));
    q.pop();
  }
}