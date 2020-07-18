#include "../headers/LogInController.h"


LogInController::LogInController(int& argc, char* argv[],
                                 ClientConnector& clientConnector) : 
                                        app(argc,argv),logIn(clientConnector) {}

int LogInController::run(){
    logIn.show();
    int app_error = app.exec();
    if (app_error != 0) return app_error;
    return logIn.getExit();
}

uint16_t LogInController::getWidth(){
    return logIn.getWidth();
}
        
uint16_t LogInController::getHeigth(){
    return logIn.getHeigth();
}