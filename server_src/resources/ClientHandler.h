#include <atomic>

#include "Persistor.h"
#include "Socket.h"
#include "Thread.h"

class ClientHandler : public Thread {
 private:
  Socket peer;
  Persistor& persistor;
  std::atomic<bool> online;

 public:
  ClientHandler(Socket p, Persistor& persist);

  ~ClientHandler();

  void run() override;

  bool finished();
};
