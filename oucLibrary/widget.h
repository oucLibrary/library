#ifndef WIDGET_H
#define WIDGET_H

#include "dbdemo.h"
#include "login.h"

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTableWidget>
#include <QTabWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void createShowBook();
    void createUserWidget();
    void createRootWidget();
    ~Widget();

protected:
    void paintEvent(QPaintEvent * event);

protected slots:
    void query();
    void login_success(QString username, QString password, Identify id);
    void logout();

private:
    QComboBox * choose;        //选择查询目标
    QLineEdit * context;       //查询内容
    QPushButton * start;       //开始查询
    QPushButton * log;         //登录
    QPushButton * showName;    //显示帐号名称
    QPushButton * lot;         //注销
    Login * logins;                  //登陆界面
    QTableWidget * showBookResult;   //显示查询图书结果
    QTabWidget * userWidget;         //显示用户界面
    QTabWidget * rootWidget;         //显示管理员界面

    QString username;
    QString password;
    Identify id;
};

#endif // WIDGET_H
