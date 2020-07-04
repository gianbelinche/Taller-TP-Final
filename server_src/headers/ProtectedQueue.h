#ifndef PROTECTEDQUEUE_H
#define PROTECTEDQUEUE_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <queue>
#include <utility>
#include <vector>

#include "ClosedQueueException.h"

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

template <class T>
ProtectedQueue<T>::ProtectedQueue() : closed(false), enabled(true) {}

template <class T>
ProtectedQueue<T>::~ProtectedQueue() {}

template <class T>
void ProtectedQueue<T>::close() {
  std::unique_lock<std::mutex> l(m);
  closed = true;
  cv.notify_all();
}

template <class T>
void ProtectedQueue<T>::push(T s) {
  std::unique_lock<std::mutex> l(m);
  q.push(std::move(s));
  cv.notify_all();  // O one, no cambia nada en nuestro caso, solo va a haber 1
                    // en espera
}

template <class T>
T ProtectedQueue<T>::pop() {
  std::unique_lock<std::mutex> l(m);
  while (q.empty()) {
    if (closed) {
      throw ClosedQueueException("La cola esta cerrada");
    }
    cv.wait(l);
  }
  T poppedMsg = q.front();
  q.pop();
  return poppedMsg;
}

template <class T>
void ProtectedQueue<T>::emptyQueue(std::vector<T> &events) {
  std::unique_lock<std::mutex> l(m);
  while (!q.empty()) {
    events.push_back(std::move(q.front()));
    q.pop();
  }
}

template <class T>
bool ProtectedQueue<T>::isClosed() {
  return closed;
}

template <class T>
bool ProtectedQueue<T>::empty() {
  return q.empty();
}

template <class T>
void ProtectedQueue<T>::disable() {
  enabled = false;
}

template <class T>
void ProtectedQueue<T>::enable() {
  enabled = true;
}

template <class T>
bool ProtectedQueue<T>::isEnabled() {
  return enabled;
}

#endif  // PROTECTEDQUEUE_H
