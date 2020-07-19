#include "../headers/Acceptor.h"

#include <utility>
#include <vector>

Acceptor::Acceptor(const char* serv) {
  sock.bind(serv);
  sock.listen();
}

Acceptor::~Acceptor() {}

Socket Acceptor::accept() {
  Socket peer = sock.accept();
  return peer;
}

void Acceptor::close() {
  sock.shutdown_close();
}

