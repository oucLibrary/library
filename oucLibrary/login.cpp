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
    /*string name;
    for(int i=0;i<50;i++)
        name.push_back(0);
    name="oucLibrary";
    char account[20];
    memset(account,0,sizeof(account));
    char passwo[20];
    memset(passwo,0,sizeof(passwo));
    strcpy(account, "14020031000");
    strcpy(passwo,"123456");
    Admins * admin = new Admins(0,name,account,passwo);
    file->FileWrite((DbDemo *)admin);*/

    for(int i=1; i<=file->GetCount(); i++)
    {
        char * ans = new char[1000];
        ans = file->PrintFile(i, 1);
        for(int j=0; j<username->text().length(); j++)
        {
            if(username->text()[j] != ans[j+sizeof(int)+50])
                break;
            if(j == username->text().length()-1)
                ok = true;
        }
        if(ok)
        {
            for(int j=0; j<password->text().length(); j++)
            {
                if(password->text()[j] != ans[j+sizeof(int)+70])
                    ok = false;
            }
        }
        if(ok)
            break;
    }
    delete file;
    if(!ok)
    {
        id = User;
        DbDemoFileOperate * file = new DbDemoFileOperate("./user/user.dat");
        /*string name;
        for(int i=0;i<50;i++)
            name.push_back(0);
        name="世界你好";
        char account[20];
        memset(account,0,sizeof(account));
        char passwo[20];
        memset(passwo,0,sizeof(passwo));
        strcpy(account, "14020031543");
        strcpy(passwo,"123456");
        char email[50];
        memset(email,0,sizeof(email));
        strcpy(email,"123456789@qq.com");
        char phone[15];
        memset(phone,0,sizeof(phone));
        strcpy(phone,"17854282345");
        Persons * person = new Persons(0,name,account,passwo,'M',email,phone,21,QDate(1996,8,25));
        file->FileWrite((DbDemo *)person);*/
        for(int i=1; i<=file->GetCount(); i++)
        {
            char * ans = new char[1000];
            ans = file->PrintFile(i, 1);
            for(int j=0; j<username->text().length(); j++)
            {
                if(username->text()[j] != ans[j+sizeof(int)+50])
                    break;
                if(j == username->text().length()-1)
                    ok = true;
            }
            if(ok)
            {
                for(int j=0; j<password->text().length(); j++)
                {
                    if(password->text()[j] != ans[j+sizeof(int)+70])
                        ok = false;
                }
            }
            if(ok)
                break;
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
