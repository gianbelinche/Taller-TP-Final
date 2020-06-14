

#include "Thread.h"
#include "Events/UserMoved.h"

class ServerEventHandler {
private:

public:
  ServerEventHandler();

  ~ServerEventHandler();

  void handle(UserMoved ev);
};