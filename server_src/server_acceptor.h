#include <atomic>
#include <vector>

#include "common_Socket.h"
#include "common_client_handler.h"
#include "common_Thread.h"

class Acceptor : public Thread{
private:
  Socket sock;
  std::vector<ClientHandler*> clients;
  std::vector<int> numbers;
  std::atomic<bool> keep_talking;
  Scorer score;

public:
  Acceptor(const char* serv, std::vector<int> &nums);

  ~Acceptor();

  virtual void run() override;

  void release_dead_clients();

  void release_all_clients();

  void stop_accepting();
};

