#include "LogInController.h"


LogInController::LogInController(int& argc, char* argv[],
ClientConnector& clientConnector) : app(argc,argv),logIn(clientConnector) {}

int LogInController::run(){
    logIn.show();
    return app.exec();
}