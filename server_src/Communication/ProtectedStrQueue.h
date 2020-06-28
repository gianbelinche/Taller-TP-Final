#ifndef PROTECTED_STR_QUEUE
#define PROTECTED_STR_QUEUE

#include <mutex>
#include <queue>
#include <string>
#include <vector>

class ProtectedStrQueue {
 private:
  std::mutex m;
  std::queue<std::string> q;

 public:
  ProtectedStrQueue();

  ~ProtectedStrQueue();

  void push(std::string s);

  // Pre: La cola no esta vacia
  std::string pop();

  bool empty();

  void emptyQueue(std::vector<std::string> &events);
};

#endif
