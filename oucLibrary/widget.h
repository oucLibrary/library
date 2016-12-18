#ifndef WIDGET_H
#define WIDGET_H

#include "dbdemo.h"
#include "login.h"
#include "tablewidget.h"
#include "dialog.h"
#include "test.h"

#include <QWidget>
#include <QPushButton>
#include <QComboBox>
#include <QLineEdit>
#include <QTabWidget>
#include <QCheckBox>

enum Ope_aim {
    Book, Borrow, Person
};

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    void createDialog();
    void createShowResult();
    void createUserWidget();
    void createRootWidget();
    ~Widget();

protected:
    void paintEvent(QPaintEvent * event);

protected slots:
    void initResult(int index = -1);
    void query();
    void login_success(QString username, QString password, int num, Identify id);
    void logout();
    void showResult(int page = 1);
    void chooseChange(int index = 0);
    void returnBook();
    void deleteUser();
    bool addUsers(QList<QString> list, bool warn = true);
    void addBorrow();
    bool addNewBooks(QList<QString> list, bool warn = true);
    void addCurrBooks(QList<QString> list);
    void delBooks();
    void changeBooks();
    void addBorrows(QList<QString>list);
    void deleteBook(QList<QString>list);
    void lendAgain2();
    void inputFromFile();

private:
    QComboBox * choose;        //选择查询目标
    QLineEdit * context;       //查询内容
    QPushButton * start;       //开始查询
    QPushButton * log;         //登录
    QPushButton * showName;    //显示帐号名称
    QPushButton * lot;         //注销
    Login * logins;                  //登陆界面
    TableWidget * showResults[3];    //显示查询图书结果,借阅记录,用户列表
    int oks[3];                      //写到哪个缓存文件
    vector<int> show_id[3];          //对应显示内容的id
    QTabWidget * userWidget;         //显示用户界面
    QTabWidget * rootWidget;         //显示管理员界面
    QCheckBox * checkbox;            //是否从当前目录查询
    QPushButton * resetButton;        //重置按钮
    QPushButton * addCurrBook;       //增加当前书
    QPushButton * addNewBook;        //增加新书
    QPushButton * delBook;           //删除书
    QPushButton * retBook;           //还书
    QPushButton * losBook;           //丢失书
    QPushButton * addPerson;         //增加用户
    QPushButton * delPerson;         //删除用户
    QPushButton * lendBook;          //借书
    QPushButton * changeBook;        //修改书
    QPushButton * lendAgain;         //续借
    QPushButton * chooseFile;     //从文件导入
    Dialog * addUser;                //输入添加的用户的信息
    Dialog * borrowBook;             //输入添加的借书信息
    Dialog * newBook;                //新书信息
    Dialog * currBook;               //当前书信息
    Dialog * dBook;                  //要删除的书的信息

    QString username;
    QString password;
    int num;
    Identify id;

    DbDemoFileOperate * file[3];
    DbDemoFileOperate * result[3];
    Ope_aim ope_aim;
    test * changeInfor;
};

#endif // WIDGET_H
