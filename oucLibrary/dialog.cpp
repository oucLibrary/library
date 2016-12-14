#include "dialog.h"

#include <QMessageBox>
#include <QDebug>

Dialog::Dialog(int inputNum,vector<string> shows) :inputNum(inputNum), shows(shows)
{
    setMaximumSize(300, shows.size()*50+30);
    setMinimumSize(300, shows.size()*50+30);

    labels = new QLabel*[(int)shows.size()];
    lineedits = new QLineEdit*[(int)shows.size()];
    ok = false;
    for(int i=0; i<(int)shows.size(); i++)
    {
        labels[i] = new QLabel(QString::fromStdString(shows[i]),this);
        labels[i]->setGeometry(10,10+(i-(ok>0)*inputNum)*50,60,30);
        if(shows[i] == "性别")
        {
            sex = new QComboBox(this);
            sex->addItem("男");
            sex->addItem("女");
            sex->setGeometry(90, 10+(i-(ok>0)*inputNum)*50, 200, 30);
            continue;
        }
        else if(shows[i] == "生日")
        {
            birth = new QDateEdit(this);
            birth->setGeometry(90, 10+(i-(ok>0)*inputNum)*50, 200, 30);
            birth->setCalendarPopup(true);
            continue;
        }
        else if(shows[i] == "图书id")
        {
            bookId = new QComboBox(this);
            bookId->setGeometry(90, 10+i*50, 200, 30);
            for(int j=i+1;j<=i+inputNum;j++)
                bookId->addItem(QString::fromStdString(shows[j]));
            setMaximumSize(300, (shows.size()-inputNum)*50+30);
            setMinimumSize(300, (shows.size()-inputNum)*50+30);
            ok = i+1;
            i+=inputNum;
            continue;
        }
        lineedits[i] = new QLineEdit(this);
        lineedits[i]->setGeometry(90, 10+(i-(ok>0)*inputNum)*50, 200, 30);
    }

    confirm = new QPushButton("确定", this);
    confirm->setGeometry(25, (shows.size()-(ok>0)*inputNum)*50, 100, 20);
    cancel = new QPushButton("取消", this);
    cancel->setGeometry(175, (shows.size()-(ok>0)*inputNum)*50, 100, 20);

    connect(confirm,SIGNAL(clicked(bool)),this,SLOT(confirmSubmit()));
    connect(cancel,SIGNAL(clicked(bool)),this,SLOT(close()));
}

void Dialog::confirmSubmit()
{
    QList<QString>list;
    int num = shows.size();
    if(ok)
        num-=inputNum;
    for(int i=0; i<num; i++)
    {
        if(shows[i+((i>=ok)&&ok)*inputNum] == "性别")
            list << sex->currentText();
        else if(shows[i+((i>=ok)&&ok)*inputNum] == "生日")
            list << birth->dateTime().toString("yyyy-MM-dd");
        else if(shows[i+((i>=ok)&&ok)*inputNum] == "图书id")
            list << bookId->currentText();
        else
            list << lineedits[i+((i>=ok)&&ok)*inputNum]->text();
        if(list.at(i+((i>=ok)&&ok)*inputNum).isEmpty() || list.at(i+((i>=ok)&&ok)*inputNum).contains(" "))
        {
            QMessageBox::warning(this,"操作失败",QString("%1不能为空且不能含空格").arg(QString::fromStdString(shows[i+((i>=ok)&&ok)*inputNum])));
            return;
        }
    }
    emit submit(list);
    close();
}
