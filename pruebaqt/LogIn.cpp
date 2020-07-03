#include "LogIn.h"

#include <QDesktopWidget>

#include <iostream> //sacar, solo para ejemplo

LogIn::LogIn(QMainWindow *parent) : QMainWindow(parent),
                                    centralWidget(this),
                                    button1(&centralWidget),
                                    button2(&centralWidget),
                                    lineEdit1(&centralWidget),
                                    lineEdit2(&centralWidget),
                                    label1(&centralWidget),
                                    label2(&centralWidget),
                                    comboBox1(&centralWidget),
                                    comboBox2(&centralWidget) {
    if (this->objectName().isEmpty())
        this->setObjectName(QStringLiteral("LogIn"));
    this->resize(640, 480);
    this->setMinimumSize(QSize(640, 480));
    this->setMaximumSize(QSize(640, 480));
    this->setStyleSheet(QStringLiteral("background-image: url(img/background.png)"));
    QRect screenGeometry = QApplication::desktop()->availableGeometry();
    int x = (screenGeometry.width() - this->width()) / 2;
    int y = (screenGeometry.height() - this->height()) / 2;
    this->move(x, y);

    this->setUpFirst();
    this->setEventsFirst();
}

LogIn::~LogIn() {
    this->exitApp();
}

void LogIn::exitApp() {
    this->button1.close();
    this->button2.close();
    this->lineEdit1.close();
    this->lineEdit2.close();
    this->label1.close();
    this->label2.close();
    this->comboBox1.close();
    this->comboBox2.close();
    this->close();
}

void LogIn::setEventsFirst() {
    // Conecto el evento del boton connect
    QObject::connect(&this->button1, &QPushButton::clicked,
                     this, &LogIn::connectSrv);

    // Conecto el evento del boton exit
    QObject::connect(&this->button2, &QPushButton::clicked,
                     this, &LogIn::exitApp);
}

void LogIn::setUpFirst() {
    this->centralWidget.setObjectName(QStringLiteral("centralwidget"));
    
    QFont font;
    font.setFamily(QStringLiteral("Verdana"));
    font.setPointSize(12);
    font.setItalic(false);

    this->button1.setObjectName(QStringLiteral("pushButton"));
    this->button1.setGeometry(QRect(250, 290, 111, 31));
    this->button1.setFont(font);
    
    this->button2.setObjectName(QStringLiteral("pushButton_2"));
    this->button2.setGeometry(QRect(260, 350, 89, 25));
    this->button2.setFont(font);
    
    this->lineEdit1.setObjectName(QStringLiteral("lineEdit"));
    this->lineEdit1.setGeometry(QRect(190, 150, 271, 29));
    this->lineEdit1.setFont(font);
    
    this->lineEdit2.setObjectName(QStringLiteral("lineEdit_2"));
    this->lineEdit2.setGeometry(QRect(190, 220, 271, 29));
    this->lineEdit2.setFont(font);
    
    this->label1.setObjectName(QStringLiteral("label"));
    this->label1.setGeometry(QRect(140, 140, 75, 51));
    this->label1.setFont(font);
    this->label1.setStyleSheet(QStringLiteral("background: transparent"));
    
    this->label2.setObjectName(QStringLiteral("label_2"));
    this->label2.setEnabled(true);
    this->label2.setGeometry(QRect(140, 210, 75, 51));
    this->label2.setFont(font);
    this->label2.setLayoutDirection(Qt::LeftToRight);
    this->label2.setAutoFillBackground(false);
    this->label2.setStyleSheet(QStringLiteral("background: transparent"));
    this->label2.setScaledContents(false);

    this->setCentralWidget(&centralWidget);

    this->setWindowTitle(QApplication::translate("LogIn", "MainWindow", Q_NULLPTR));
    this->button1.setText(QApplication::translate("LogIn", "Connect", Q_NULLPTR));
    this->button2.setText(QApplication::translate("LogIn", "Exit", Q_NULLPTR));
    this->label1.setText(QApplication::translate("LogIn", "Host", Q_NULLPTR));
    this->label2.setText(QApplication::translate("LogIn", "Port", Q_NULLPTR));

    this->comboBox1.hide();
    this->comboBox2.hide();
}

void LogIn::setUpSecond() {
    this->button1.setText("Login");
    this->label1.setText("Account");
    this->label2.setText("Password");
    this->label1.move(105, 140);
    this->label2.move(105, 210);
    this->lineEdit1.clear();
    this->lineEdit2.clear();

    //this->comboBox1.show(); <- esto va en el panel de crear caracter
    //this->comboBox2.show(); <- esto va en el panel de crear caracter
}

void LogIn::setEventsSecond() {
    //aca se tendria que cambiar el evento de los botones
}

void LogIn::connectSrv() {
    /*Esto es solo un ejemplo*/

    //con *->text() obtengo lo ingresado por el usuario
    std::cout << "Host: " << this->lineEdit1.text().toStdString() << '\n';
    std::cout << "Port: " << this->lineEdit2.text().toStdString() << '\n';

    // Este if lo hice simulando que puso un host y un puerto y se conecto existosamente
    // Aca sería if connect hace algo asi, else mostrar msg de error.
    // Esto de abajo se puede hacer en una funcion aparte y además habría que actualizar
    // los eventos de los botones como en connectEvents
    if (this->lineEdit1.text().toStdString() == "localhost" && this->lineEdit2.text().toStdString() == "8080") {
        this->setUpSecond();
        this->setEventsSecond();
    }
}
