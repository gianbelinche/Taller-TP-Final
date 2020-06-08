

#include "Thread.h"
#include "UserMoved.h"

class ServerEventHandler {
private:

public:
  ServerEventHandler();

  ~ServerEventHandler();

  void handle(UserMoved ev);
};