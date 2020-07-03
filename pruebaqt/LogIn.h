#ifndef __LOG_IN_H__
#define __LOG_IN_H__

#include <QMainWindow>

class LogIn : public QMainWindow {
public:
    explicit LogIn(QMainWindow *parent = 0);
private:
    void exitApp();
    void connectSrv();
    void connectEvents();
};

#endif // __LOG_IN_H__
