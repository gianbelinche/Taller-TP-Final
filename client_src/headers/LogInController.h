#ifndef CLASS_LOGIN_CONTROLLER
#define CLASS_LOGIN_CONTROLLER
#include "LogIn.h"
#include "ClientConnector.h"
#include <QtWidgets/QApplication>

class LogInController{
private:
    QApplication app;
    LogIn logIn;
public:
    LogInController(int& argc, char* argv[],ClientConnector& clientConnector);
    int run();
    uint16_t getWidth();
    uint16_t getHeigth();
};

#endif
