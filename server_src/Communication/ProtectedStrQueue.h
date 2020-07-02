#ifndef PROTECTED_STR_QUEUE
#define PROTECTED_STR_QUEUE

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <string>
#include <vector>

class ProtectedStrQueue {
 private:
  std::mutex m;
  std::queue<std::string> q;
  std::condition_variable cv;
  std::atomic<bool> closed;

 public:
  ProtectedStrQueue();

  ~ProtectedStrQueue();

  void close();

  void push(std::string s);

  std::string pop();

  bool empty();

  // Vacia la colay pone sus elementos en events, la cola permanece bloqueda
  // durante este proceso
  void emptyQueue(std::vector<std::string> &events);
};

#endif
