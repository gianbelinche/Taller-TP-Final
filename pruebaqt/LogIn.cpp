#include "LogIn.h"
#include "ui_login.h"

LogIn::LogIn(QMainWindow *parent) : QMainWindow(parent) {
    // Instancio la configuracion generada por el designer y uic
    Ui::LogIn logIn;
    // Configuro este widget para use esa configuracion
    logIn.setupUi(this);
    connectEvents();
}

void LogIn::exitApp() {
    this->close();
}

#include <iostream>

void LogIn::connectSrv() {
    /*Esto es solo un ejemplo*/
    QLineEdit* host = findChild<QLineEdit*>("lineEdit");
    QLineEdit* port = findChild<QLineEdit*>("lineEdit_2");

    std::cout << "Host: " << host->text().toStdString() << '\n';
    std::cout << "Port: " << port->text().toStdString() << '\n';
}

void LogIn::connectEvents() {
    // Conecto el evento del boton
    QPushButton* buttonConnect = findChild<QPushButton*>("pushButton");
    QObject::connect(buttonConnect, &QPushButton::clicked,
                     this, &LogIn::connectSrv);

    QPushButton* buttonExit = findChild<QPushButton*>("pushButton_2");
    QObject::connect(buttonExit, &QPushButton::clicked,
                     this, &LogIn::exitApp);
}
