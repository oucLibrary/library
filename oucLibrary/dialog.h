#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDateEdit>
#include <bits/stdc++.h>
using namespace std;

class Dialog : public QDialog
{
    Q_OBJECT
public:
    explicit Dialog(int inputNum,vector<string> shows);

signals:
    void submit(QList<QString>list);

protected slots:
    void confirmSubmit();

private:
    int inputNum;
    vector<string> shows;
    QLabel ** labels;
    QLineEdit ** lineedits;
    QPushButton * confirm;
    QPushButton * cancel;
    QComboBox * sex;
    QComboBox * bookId;
    QDateEdit * birth;

    int ok;           //输入目录里面输入图书id是第几条
};

#endif // DIALOG_H
