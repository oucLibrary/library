#ifndef REGISTER_H
#define REGISTER_H

#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

class Register : public QWidget
{
    Q_OBJECT
public:
    explicit Register(QWidget *parent = 0);
    ~Register();

signals:
    void register_success(QString username, QString password);

public slots:
    void check();

private:
    QLabel * showname;
    QLabel * showpass;
    QLineEdit * username;
    QLineEdit * password;
    QPushButton * confirm;
    QPushButton * cancel;
};

#endif // REGISTER_H
