#include "Socket.h"
#include "Thread.h"
#include "Persistor.h"

class ClientHandler
{
private:
  Socket peer;
  Persistor& persistor;
public:
  ClientHandler(Socket p, Persistor& persist);

  ~ClientHandler();
};
