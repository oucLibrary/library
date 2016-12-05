#ifndef LOGIN_H
#define LOGIN_H

#include "register.h"

#include <QWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

enum Identify {
    Empty, User, Root
};

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget * parent = 0);
    ~Login();

signals:
    void login_success(QString username, QString password, int num, Identify id = User);

protected slots:
    void check();
    void register_success(QString username, QString password);

private:
    QLabel * showname;
    QLabel * showpass;
    QLineEdit * username;
    QLineEdit * password;
    QPushButton * log;
    QPushButton * reg;

    Register * regist;
};

#endif // LOGIN_H
