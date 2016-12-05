#include "login.h"
#include "dbdemo.h"

#include <QMessageBox>
#include <QDate>
#include <QDebug>

Login::Login(QWidget * parent) : QWidget(parent), showname(new QLabel(this)), showpass(new QLabel(this)),
    username(new QLineEdit(this)), password(new QLineEdit(this)), log(new QPushButton(this)), reg(new QPushButton(this)),
    regist(new Register())
{
    setWindowModality(Qt::ApplicationModal);

    setMaximumSize(400, 200);
    setMinimumSize(400, 200);

    showname->setGeometry(60, 40, 60, 30);
    showname->setText("帐号");

    username->setGeometry(150, 40, 180, 30);

    showpass->setGeometry(60, 90, 60, 30);
    showpass->setText("密码");

    password->setGeometry(150, 90, 180, 30);

    log->setGeometry(60, 150, 120, 30);
    log->setText("登录");
    connect(log, SIGNAL(clicked(bool)), this, SLOT(check()));

    reg->setGeometry(210, 150, 120, 30);
    reg->setText("注册");
    connect(reg, SIGNAL(clicked(bool)), this, SLOT(hide()));
    connect(reg, SIGNAL(clicked(bool)), regist, SLOT(show()));

    connect(regist, SIGNAL(register_success(QString,QString)), this, SLOT(register_success(QString,QString)));
}

void Login::check()
{
    bool ok = false;
    //判断登录是否成功以及是什么身份登录的
    Identify id = Root;
    DbDemoFileOperate * file = new DbDemoFileOperate("./admin/admin.dat");
    /*QString account,passwd;
    account="14020031000";
    passwd="123456";
    Admins * admin = new Admins(0,account,passwd);
    file->FileWrite((DbDemo *)admin);*/

    for(int i=1; i<=file->GetCount(); i++)
    {
        Admins * admin = new Admins(file->PrintFile(i,1));
        if(!strcmp(admin->Getaccount(), username->text().toStdString().c_str()))
            if(!strcmp(admin->Getpassword(), password->text().toStdString().c_str()))
            {
                ok = true;
                break;
            }
    }
    delete file;
    if(!ok)
    {
        id = User;
        DbDemoFileOperate * file = new DbDemoFileOperate("./person/person.dat");
        for(int i=1; i<=file->GetCount(); i++)
        {
            Persons * person = (Persons *)file->PrintFile(i,1);
            if(!strcmp(person->Getaccount(), username->text().toStdString().c_str()))
                if(!strcmp(person->Getpassword(), password->text().toStdString().c_str()))
                {
                    ok = true;
                    break;
                }
        }
    }
    if(!ok)
    {
        QMessageBox * mess = new QMessageBox(this);
        mess->setText("帐号或密码错误");
        mess->exec();
    }
    else
    {
        emit login_success(username->text(), password->text(), id);
        close();
    }
}

void Login::register_success(QString username, QString password)
{
    emit login_success(username, password);
}

Login::~Login()
{

}
