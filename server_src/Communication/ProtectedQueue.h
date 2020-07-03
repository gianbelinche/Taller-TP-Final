#ifndef PROTECTEDQUEUE_H
#define PROTECTEDQUEUE_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <vector>

template <class T>
class ProtectedQueue {
 private:
  std::mutex m;
  std::queue<T> q;
  std::condition_variable cv;
  std::atomic<bool> closed;
  bool enabled; // Indica si la cola esta lista para recibir mensajes
 public:
  ProtectedQueue();

  ~ProtectedQueue();

  void disable();

  void enable();

  bool isEnabled();

  void close();

  bool isClosed();

  void push(T s);

  T pop();

  bool empty();

  // Vacia la cola y pone sus elementos en events, la cola permanece bloqueda
  // durante este proceso
  void emptyQueue(std::vector<T> &events);
};

#endif  // PROTECTEDQUEUE_H
