#ifndef CLASS_CLIENT_INITIALIZER
#define CLASS_CLIENT_INITIALIZER

#include "ClientConnector.h"
#include "LogInController.h"
#include "MainWindow.h"

class ClientInitializer{
public:
    void run(LogInController &logInController, ClientConnector &clientConnector);
};

#endif