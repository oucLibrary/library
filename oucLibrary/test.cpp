#include "test.h"
#include "ui_test.h"
#include <QDebug>
#include <QMessageBox>

test::test(int id) :
    ui(new Ui::test)
{
    ui->setupUi(this);
    tmp=new DbDemoFileOperate("./persons/persons.dat");
    if(!tmp->Getbyid(id))
        QMessageBox::information(NULL, "Title", "用户id错误", QMessageBox::Yes | QMessageBox::Yes);
    me=new Persons(tmp->Gettmp_sto());
    ui->name->setEnabled(0);
    ui->name->setText(QString(me->Getname()));
    ui->password->setEnabled(0);
    ui->password->setText(me->Getpassword());
    ui->age->setEnabled(0);
    ui->age->setText(QString("%1").arg(me->Getage()));
    ui->email->setEnabled(0);
    ui->email->setText(me->Getemail());
    ui->phone->setEnabled(0);
    ui->phone->setText(me->Getphone());
    ui->sex->setEnabled(0);
    ui->sex->setCurrentIndex(!me->Getsex());
}

test::~test()
{
    delete ui;
}

void test::updat_confirm(){
    bool ok=1;
    if(ui->c_password->isChecked()){
        if(ui->password->text().length()==0)ok=0;
    }
    if(ui->c_name->isChecked()){
        if(ui->name->text().length()==0)ok=0;
    }
    if(ui->c_email->isChecked()){
        if(ui->email->text().length()==0)ok=0;
    }
    if(ui->c_age->isChecked()){
        if(ui->age->text().length()==0||ui->age->text().toInt()<=0)ok=0;
    }
    if(ui->c_phone->isChecked()){
        if(ui->phone->text().length()==0||ui->phone->text().toLongLong()<=0)ok=0;
    }
    ui->confirm->setEnabled(ok);
}

void test::on_password_textChanged(const QString &arg1)
{
    updat_confirm();
}

void test::on_name_textChanged(const QString &arg1)
{
    updat_confirm();
}

void test::on_email_textChanged(const QString &arg1)
{
    updat_confirm();
}

void test::on_phone_textChanged(const QString &arg1)
{
    updat_confirm();
}

void test::on_age_textChanged(const QString &arg1)
{
    updat_confirm();
}

void test::on_c_password_clicked()
{
    ui->password->setEnabled(ui->c_password->isChecked());
    if(!ui->password->isEnabled()){
        ui->password->setText(me->Getpassword());
    }
}


void test::on_c_name_clicked()
{
    ui->name->setEnabled(ui->c_name->isChecked());
    if(!ui->name->isEnabled()){
        ui->name->setText(me->Getname());
    }
}


void test::on_c_sex_clicked()
{
    ui->sex->setEnabled(ui->c_sex->isChecked());
    if(!ui->sex->isEnabled()){
        ui->sex->setCurrentIndex(me->Getsex());
    }
}

void test::on_c_email_clicked()
{
    ui->email->setEnabled(ui->c_email->isChecked());
    if(!ui->email->isEnabled()){
        ui->email->setText(me->Getemail());
    }
}

void test::on_c_phone_clicked()
{
    ui->phone->setEnabled(ui->c_phone->isChecked());
    if(!ui->phone->isEnabled()){
        ui->phone->setText(me->Getemail());
    }
}


void test::on_c_age_clicked()
{
    ui->age->setEnabled(ui->c_age->isChecked());
    if(!ui->age->isEnabled()){
        ui->age->setText(QString("%1").arg(me->Getage()));
    }
}

void test::on_confirm_clicked()
{
    if(ui->c_age->isChecked())me->Setage(ui->age->text().toInt());
    if(ui->c_email->isChecked())me->Setemail(ui->email->text());
    if(ui->c_name->isChecked())me->Setname(ui->name->text());
    if(ui->c_password->isChecked())me->Setpassword(ui->password->text());
    if(ui->c_phone->isChecked())me->Setphone(ui->phone->text());
    if(ui->c_sex->isChecked())me->Setsex(ui->sex->currentIndex());
    tmp->Changebyid(me->GetId(),me->Getmy_cache());
    hide();
}

void test::on_cancel_clicked()
{
    hide();
}

void test::deleteThis()
{
    delete this;
}
