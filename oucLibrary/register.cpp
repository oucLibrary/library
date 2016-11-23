#include "register.h"

#include <QMessageBox>

Register::Register(QWidget *parent) : QWidget(parent), showname(new QLabel(this)), showpass(new QLabel(this)),
    username(new QLineEdit(this)), password(new QLineEdit(this)), confirm(new QPushButton(this)),
    cancel(new QPushButton(this))
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

    confirm->setGeometry(60, 150, 120, 30);
    confirm->setText("注册");
    connect(confirm, SIGNAL(clicked(bool)), this, SLOT(check()));

    cancel->setGeometry(210, 150, 120, 30);
    cancel->setText("取消");
    connect(cancel, SIGNAL(clicked(bool)), this, SLOT(hide()));
}

void Register::check()
{
    bool ok = false;
    //判断注册是否可以
    if(!ok)
    {
        QMessageBox * mess = new QMessageBox();
        mess->setText("注册失败");
        mess->exec();
    }
    else
    {
        QMessageBox * mess = new QMessageBox();
        mess->setText("注册成功");
        mess->exec();
        emit register_success(username->text(), password->text());
    }
}

Register::~Register()
{

}

