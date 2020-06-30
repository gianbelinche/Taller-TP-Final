#include <atomic>
#include <vector>

#include "Socket.h"
#include "Thread.h"

class Acceptor : public Thread{
private:
  Socket sock;
  std::vector<ClientHandler*> clients;
  std::atomic<bool> keep_talking;

public:
  Acceptor(const char* serv);

  ~Acceptor();

  virtual void run() override;

  void release_dead_clients();

  void release_all_clients();

  void stop_accepting();
};

