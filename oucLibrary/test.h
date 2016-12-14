#ifndef TEST_H
#define TEST_H

#include <QDialog>
#include "dbdemo.h"

namespace Ui {
class test;
}

class test : public QDialog
{
    Q_OBJECT

public:
    explicit test(int id);
    ~test();
    void updat_confirm();
private slots:
    void on_password_textChanged(const QString &arg1);

    void on_name_textChanged(const QString &arg1);

    void on_email_textChanged(const QString &arg1);

    void on_phone_textChanged(const QString &arg1);

    void on_age_textChanged(const QString &arg1);

    void on_c_password_clicked();

    void on_c_name_clicked();

    void on_c_sex_clicked();

    void on_c_email_clicked();

    void on_c_phone_clicked();

    void on_c_age_clicked();

    void on_confirm_clicked();

    void on_cancel_clicked();

protected slots:
    void deleteThis();

private:
    Ui::test *ui;
    DbDemoFileOperate *tmp;
    Persons *me;
};

#endif // TEST_H
