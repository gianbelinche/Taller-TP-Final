#include "LogIn.h"

#include <QtWidgets/QDesktopWidget>
#include <msgpack.hpp>
#include "SocketException.h"
#include <sstream>
#include <string>
#include "QuitException.h"

#include <iostream> //sacar, solo para ejemplo


/*#include <QCloseEvent>

void LogIn::closeEvent(QCloseEvent *event){
    this->exitEntireApp();
    event->accept();
}*/


LogIn::LogIn(ClientConnector& clientConnector,QMainWindow *parent) :
                                    QMainWindow(parent),
                                    centralWidget(this),
                                    button1(&centralWidget),
                                    button2(&centralWidget),
                                    lineEdit1(&centralWidget),
                                    lineEdit2(&centralWidget),
                                    label1(&centralWidget),
                                    label2(&centralWidget),
                                    comboBox1(&centralWidget),
                                    comboBox2(&centralWidget),
                                    clientConnector(clientConnector),
                                    normal_exit(0) {
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

void LogIn::exitEntireApp(){
    this->exitApp();
    normal_exit = -1;
}

void LogIn::setEventsFirst() {
    // Conecto el evento del boton connect
    QObject::connect(&this->button1, &QPushButton::clicked,
                     this, &LogIn::connectSrv);

    // Conecto el evento del boton exit
    QObject::connect(&this->button2, &QPushButton::clicked,
                     this, &LogIn::exitEntireApp);
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

void LogIn::setEventsSecond() {
    // Desconecto evento del boton connect -> signIn
    QObject::disconnect(&this->button1, &QPushButton::clicked,
                        this, &LogIn::connectSrv);
    // Conecto evento del boton signIn (ex connect)
    QObject::connect(&this->button1, &QPushButton::clicked,
                     this, &LogIn::signIn);
}

void LogIn::setUpSecond() {
    this->button1.setText("Login");
    this->label1.setText("Account");
    this->label2.setText("Password");
    this->label1.move(105, 140);
    this->label2.move(105, 210);
    this->lineEdit1.clear();
    this->lineEdit2.clear();
}

void LogIn::setUpThird() {
    this->lineEdit1.hide();
    this->lineEdit2.hide();

    this->comboBox1.setObjectName(QStringLiteral("comboBox"));
    this->comboBox1.setGeometry(QRect(252, 180, 110, 25));
    this->comboBox1.show();
    this->comboBox2.setObjectName(QStringLiteral("comboBox_2"));
    this->comboBox2.setGeometry(QRect(252, 250, 110, 25));
    this->comboBox2.show();
    this->label1.setGeometry(QRect(257, 140, 105, 55));
    this->label2.setGeometry(QRect(257, 210, 105, 55));
    this->label1.setText("Choose Race");
    this->label2.setText("Choose Class");

    this->comboBox1.clear();
    this->comboBox1.insertItems(0, QStringList()
        << QApplication::translate("LogIn", "Humano", Q_NULLPTR)
        << QApplication::translate("LogIn", "Elfo", Q_NULLPTR)
        << QApplication::translate("LogIn", "Enano", Q_NULLPTR)
        << QApplication::translate("LogIn", "Gnomo", Q_NULLPTR)
    );
    this->comboBox2.clear();
    this->comboBox2.insertItems(0, QStringList()
        << QApplication::translate("LogIn", "Guerrero", Q_NULLPTR)
        << QApplication::translate("LogIn", "Mago", Q_NULLPTR)
        << QApplication::translate("LogIn", "Cl\303\251rigo", Q_NULLPTR)
        << QApplication::translate("LogIn", "Paladin", Q_NULLPTR)
    );

    this->button1.setText("Create");
}

void LogIn::setEventsThird() {
    // Desconecto evento del boton signIn -> createChar
    QObject::disconnect(&this->button1, &QPushButton::clicked,
                        this, &LogIn::signIn);
    // Conecto evento del boton createChar (ex signin)
    QObject::connect(&this->button1, &QPushButton::clicked,
                     this, &LogIn::createChar);
}

void LogIn::connectSrv() {
    try{
        std::string host = this->lineEdit1.text().toStdString();
        std::string port = this->lineEdit2.text().toStdString();
        clientConnector.connect(host.c_str(),port.c_str());
        this->setUpSecond();
        this->setEventsSecond();
    }catch(const SocketException& e){
        this->lineEdit1.clear();
        this->lineEdit2.clear();
    }
}

void LogIn::signIn() {
    std::string username = this->lineEdit1.text().toStdString();
    std::string password = this->lineEdit2.text().toStdString();

    //Enviar username y password

    std::vector<uint32_t> int_msg;
    int_msg.emplace_back(4);
    int_msg.emplace_back(username.length());
    for (unsigned int i = 0; i < username.length();i++){
        int_msg.emplace_back(username[i]);
    }
    for (unsigned int i = 0; i < password.length();i++){
        int_msg.emplace_back(password[i]);
    }

    std::stringstream buffer;
    msgpack::pack(buffer, int_msg);
    std::string sbuffer = buffer.str();

    std::vector<char> msg(sbuffer.begin(), sbuffer.end());
    uint32_t len = htonl(msg.size());

    //enviar largo
    clientConnector.send((char*)&len, 4);

    //enviar paquete
    clientConnector.send(msg, msg.size());

    //recivo largo
    std::vector<char> longBuff = clientConnector.receive(4);
    len = *((uint32_t*)&longBuff[0]);
    len = ntohl(len);

    //recibe paquete
    std::vector<char> msgBuff = clientConnector.receive(len);
    std::string ss(msgBuff.begin(), msgBuff.end());

    //desempaqueta
    std::vector<uint32_t> response;
    msgpack::object_handle oh = msgpack::unpack(ss.data(), ss.size());
    oh.get().convert(response);

    if (response[0] == 10){
        switch (response[1]){
            case 0:
                break;
            case 1:
                this->exitApp();
                break;
            case 2:
                this->setUpThird();
                this->setEventsThird();
                break;
        }        
    }
    this->lineEdit1.clear();
    this->lineEdit2.clear();
}

int LogIn::getExit(){
    return normal_exit;
}

void LogIn::createChar() {
    std::string race = comboBox1.currentText().toStdString();
    std::string class_ = comboBox2.currentText().toStdString();

    std::cout << race << "\n" << class_ << "\n";

    std::vector<uint32_t> int_msg;
    int_msg.emplace_back(6);
    if (race == "Humano"){
        int_msg.emplace_back(0);
    }
    if (race == "Elfo"){
        int_msg.emplace_back(1);
    }
    if (race == "Enano"){
        int_msg.emplace_back(2);
    }
    if (race == "Gnomo"){
        int_msg.emplace_back(3);
    }
    if (class_ == "Guerrero"){
        int_msg.emplace_back(0);
    }
    if (class_ == "Mago"){
        int_msg.emplace_back(1);
    }
    if (class_ == "Clérigo"){
        int_msg.emplace_back(2);
    }
    if (class_ == "Paladin"){
        int_msg.emplace_back(3);
    }
    
    std::stringstream buffer;
    msgpack::pack(buffer, int_msg);
    std::string sbuffer = buffer.str();

    std::vector<char> msg(sbuffer.begin(), sbuffer.end());
    uint32_t len = htonl(msg.size());

    //enviar largo
    clientConnector.send((char*)&len, 4);

    //enviar paquete
    clientConnector.send(msg, msg.size());

    this->exitApp();
}
