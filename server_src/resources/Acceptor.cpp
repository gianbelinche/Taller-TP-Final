#include "../headers/Acceptor.h"

#include <utility>
#include <string>
#include <vector>

Acceptor::Acceptor(int serv) {
  sock.bind(std::to_string(serv).c_str());
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

