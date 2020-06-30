#include <utility>
#include <vector>

#include "server_acceptor.h"


Acceptor::Acceptor(const char* serv) 
                  : keep_talking(true) {
  sock.bind(serv);
  sock.listen();
}

Acceptor::~Acceptor() {
  sock.shutdown_close();
  release_all_clients();
  this->join();
}

void Acceptor::run() {
  Socket peer;
  int act_num = 0;
  try {
    while (keep_talking) {
      peer = sock.s_accept();
      ClientHandler* clih = new ClientHandler(numbers[act_num],
                                              std::move(peer),
                                              score);
      clients.push_back(clih);
      clih->start();
      release_dead_clients();
      act_num += 1;
      act_num %= numbers.size();
    }
  }
  catch(SocketException &e) {
    if (keep_talking) {
      throw e;
    }
  }
}

void Acceptor::release_dead_clients() {
  for (std::vector<ClientHandler*>::iterator it = clients.begin();
                                             it != clients.end(); ) {
    if ((*it)->finished()) {
      (*it)->join();
      delete *it;
      it = clients.erase(it);
    } else {
      ++it;
    }
  }
}

void Acceptor::release_all_clients() {
  for (std::vector<ClientHandler*>::iterator it = clients.begin(); 
                                             it != clients.end(); ) {
    (*it)->join();
    delete *it;
    it = clients.erase(it);
  }
}

void Acceptor::stop_accepting() {
  keep_talking = false;
}
