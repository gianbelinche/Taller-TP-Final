#include "LogIn.h"
#include "ui_login.h"

#include <iostream> //sacar, solo para ejemplo

LogIn::LogIn(QMainWindow *parent) : QMainWindow(parent) {
    Ui::LogIn logIn;
    logIn.setupUi(this);
    connectEvents();
}

void LogIn::exitApp() {
    this->close();
}

void LogIn::connectSrv() {
    /*Esto es solo un ejemplo*/
    // Obtengo la casilla de host
    QLineEdit* host = findChild<QLineEdit*>("lineEdit");
    // Obtengo la casilla de port
    QLineEdit* port = findChild<QLineEdit*>("lineEdit_2");

    //con *->text() obtengo lo ingresado por el usuario
    std::cout << "Host: " << host->text().toStdString() << '\n';
    std::cout << "Port: " << port->text().toStdString() << '\n';

    if (host->text().toStdString() == "localhost" && port->text().toStdString() == "8080") {
        QPushButton* buttonConnect = findChild<QPushButton*>("pushButton");
        QLabel* line1 = findChild<QLabel*>("label");
        QLabel* line2 = findChild<QLabel*>("label_2");
        
        buttonConnect->setText("EnterGame");
        line1->setText("Account");
        line2->setText("Password");
        host->clear();
        port->clear();
    }
}

void LogIn::connectEvents() {
    // Obtengo boton connect
    QPushButton* buttonConnect = findChild<QPushButton*>("pushButton");
    // Conecto el evento del boton connect
    QObject::connect(buttonConnect, &QPushButton::clicked,
                     this, &LogIn::connectSrv);

    // Obtengo boton exit
    QPushButton* buttonExit = findChild<QPushButton*>("pushButton_2");
    // Conecto el evento del boton exit
    QObject::connect(buttonExit, &QPushButton::clicked,
                     this, &LogIn::exitApp);
}
