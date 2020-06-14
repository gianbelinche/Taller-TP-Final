#ifndef THREAD_H
#define THREAD_H

#include <thread>

class Thread {
private:
  std::thread thread;
public:
  Thread();

  virtual ~Thread();

  Thread(const Thread&) = delete;

  Thread& operator=(const Thread&) = delete;

  Thread(Thread&& other);

  Thread& operator=(Thread&& other);

  void start();

  virtual void run() = 0;

  void join();
};

#endif
