#ifndef WIDGET_H
#define WIDGET_H

#include "dbdemo.h"
#include "login.h"
#include "tablewidget.h"

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTabWidget>

enum Ope_aim {
    Book, Borrow, Person
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void createShowResult();
    void createUserWidget();
    void createRootWidget();
    void initResult(int index);
    ~Widget();

protected:
    void paintEvent(QPaintEvent * event);

protected slots:
    void query();
    void login_success(QString username, QString password, Identify id);
    void logout();
    void showResult(int page);
    void chooseChange(int index = 0);

private:
    QComboBox * choose;        //选择查询目标
    QLineEdit * context;       //查询内容
    QPushButton * start;       //开始查询
    QPushButton * log;         //登录
    QPushButton * showName;    //显示帐号名称
    QPushButton * lot;         //注销
    Login * logins;                  //登陆界面
    TableWidget * showBookResult;    //显示查询图书结果
    TableWidget * showBorrowResult;  //显示借阅记录
    TableWidget * showUserResult;    //显示用户列表
    vector<int> show_id[3];          //对应显示内容的id
    QTabWidget * userWidget;         //显示用户界面
    QTabWidget * rootWidget;         //显示管理员界面

    QString username;
    QString password;
    Identify id;

    DbDemoFileOperate * file[3];
    DbDemoFileOperate * result[3];
    Ope_aim ope_aim;
};

#endif // WIDGET_H
