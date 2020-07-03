#ifndef __LOG_IN_H__
#define __LOG_IN_H__

#include <QtWidgets/QMainWindow>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include "ClientConnector.h"

class LogIn : public QMainWindow {
    private:
        QWidget centralWidget;
        QLineEdit lineEdit1;
        QLineEdit lineEdit2;
        QLabel label1;
        QLabel label2;
        QPushButton button1;
        QPushButton button2;
        QComboBox comboBox1;
        QComboBox comboBox2;
        ClientConnector& clientConnector;
        int normal_exit;
        

        void setUpFirst();  // Elegir server
        void setUpSecond(); // Ingresar cuenta
        void setEventsFirst();
        void setEventsSecond();
        void connectSrv();
        void exitApp();
        void signIn();
        void exitEntireApp();

    public:
        explicit LogIn(ClientConnector& clientConnector,QMainWindow *parent = 0);
        ~LogIn();
        int getExit();
};

#endif // __LOG_IN_H__
