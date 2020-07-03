#include <QApplication>
#include "LogIn.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    LogIn logIn;
    logIn.show();
    return app.exec();
}
