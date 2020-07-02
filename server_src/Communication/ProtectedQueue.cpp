#include "ProtectedQueue.h"

#include <utility>

#include "ClosedQueueException.h"

template <class T>
ProtectedQueue<T>::ProtectedQueue() {}

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
  return std::move(poppedMsg);
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
