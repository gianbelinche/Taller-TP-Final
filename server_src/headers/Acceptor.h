#ifndef ACCEPTOR_H
#define ACCEPTOR_H

#include <atomic>
#include <vector>

#include "Socket.h"
#include "Thread.h"

class Acceptor {
 private:
  Socket sock;

 public:
  explicit Acceptor(const char* serv);

  ~Acceptor();

  Socket accept();
};

#endif // ACCEPTOR_H
