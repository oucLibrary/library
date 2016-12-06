#include "changeperson.h"
#include "ui_changeperson.h"

changePerson::changePerson(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::changePerson)
{
    ui->setupUi(this);
}

changePerson::~changePerson()
{
    delete ui;
}
