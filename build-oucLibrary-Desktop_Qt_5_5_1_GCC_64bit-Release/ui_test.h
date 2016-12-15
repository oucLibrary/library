/********************************************************************************
** Form generated from reading UI file 'test.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEST_H
#define UI_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_test
{
public:
    QLineEdit *password;
    QLabel *label_3;
    QPushButton *confirm;
    QComboBox *sex;
    QCheckBox *c_email;
    QLabel *label_5;
    QLabel *label_6;
    QLineEdit *age;
    QCheckBox *c_password;
    QLabel *label;
    QCheckBox *c_age;
    QLabel *label_4;
    QCheckBox *c_name;
    QLineEdit *phone;
    QCheckBox *c_phone;
    QCheckBox *c_sex;
    QPushButton *cancel;
    QLineEdit *name;
    QLineEdit *email;
    QLabel *label_2;

    void setupUi(QWidget *test)
    {
        if (test->objectName().isEmpty())
            test->setObjectName(QStringLiteral("test"));
        test->resize(396, 351);
        password = new QLineEdit(test);
        password->setObjectName(QStringLiteral("password"));
        password->setGeometry(QRect(120, 10, 113, 27));
        label_3 = new QLabel(test);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(50, 90, 91, 31));
        confirm = new QPushButton(test);
        confirm->setObjectName(QStringLiteral("confirm"));
        confirm->setGeometry(QRect(80, 280, 99, 27));
        sex = new QComboBox(test);
        sex->setObjectName(QStringLiteral("sex"));
        sex->setGeometry(QRect(120, 90, 111, 27));
        c_email = new QCheckBox(test);
        c_email->setObjectName(QStringLiteral("c_email"));
        c_email->setGeometry(QRect(270, 130, 101, 31));
        label_5 = new QLabel(test);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(50, 170, 91, 31));
        label_6 = new QLabel(test);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(50, 210, 91, 31));
        age = new QLineEdit(test);
        age->setObjectName(QStringLiteral("age"));
        age->setGeometry(QRect(120, 220, 113, 27));
        c_password = new QCheckBox(test);
        c_password->setObjectName(QStringLiteral("c_password"));
        c_password->setGeometry(QRect(270, 10, 101, 31));
        label = new QLabel(test);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(50, 10, 91, 31));
        c_age = new QCheckBox(test);
        c_age->setObjectName(QStringLiteral("c_age"));
        c_age->setGeometry(QRect(270, 210, 101, 31));
        label_4 = new QLabel(test);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(50, 130, 91, 31));
        c_name = new QCheckBox(test);
        c_name->setObjectName(QStringLiteral("c_name"));
        c_name->setGeometry(QRect(270, 50, 101, 31));
        phone = new QLineEdit(test);
        phone->setObjectName(QStringLiteral("phone"));
        phone->setGeometry(QRect(120, 170, 113, 27));
        c_phone = new QCheckBox(test);
        c_phone->setObjectName(QStringLiteral("c_phone"));
        c_phone->setGeometry(QRect(270, 170, 101, 31));
        c_sex = new QCheckBox(test);
        c_sex->setObjectName(QStringLiteral("c_sex"));
        c_sex->setGeometry(QRect(270, 90, 101, 31));
        cancel = new QPushButton(test);
        cancel->setObjectName(QStringLiteral("cancel"));
        cancel->setGeometry(QRect(250, 280, 99, 27));
        name = new QLineEdit(test);
        name->setObjectName(QStringLiteral("name"));
        name->setGeometry(QRect(120, 50, 113, 27));
        email = new QLineEdit(test);
        email->setObjectName(QStringLiteral("email"));
        email->setGeometry(QRect(120, 130, 113, 27));
        label_2 = new QLabel(test);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 50, 91, 31));

        retranslateUi(test);

        QMetaObject::connectSlotsByName(test);
    } // setupUi

    void retranslateUi(QWidget *test)
    {
        test->setWindowTitle(QApplication::translate("test", "Form", 0));
        label_3->setText(QApplication::translate("test", "\346\200\247\345\210\253", 0));
        confirm->setText(QApplication::translate("test", "\347\241\256\350\256\244", 0));
        sex->clear();
        sex->insertItems(0, QStringList()
         << QApplication::translate("test", "\347\224\267", 0)
         << QApplication::translate("test", "\345\245\263", 0)
        );
        c_email->setText(QApplication::translate("test", "\344\277\256\346\224\271", 0));
        label_5->setText(QApplication::translate("test", "\347\224\265\350\257\235", 0));
        label_6->setText(QApplication::translate("test", "\345\271\264\351\276\204", 0));
        c_password->setText(QApplication::translate("test", "\344\277\256\346\224\271", 0));
        label->setText(QApplication::translate("test", "\345\257\206\347\240\201", 0));
        c_age->setText(QApplication::translate("test", "\344\277\256\346\224\271", 0));
        label_4->setText(QApplication::translate("test", "\351\202\256\347\256\261", 0));
        c_name->setText(QApplication::translate("test", "\344\277\256\346\224\271", 0));
        c_phone->setText(QApplication::translate("test", "\344\277\256\346\224\271", 0));
        c_sex->setText(QApplication::translate("test", "\344\277\256\346\224\271", 0));
        cancel->setText(QApplication::translate("test", "\345\217\226\346\266\210", 0));
        label_2->setText(QApplication::translate("test", "\345\247\223\345\220\215", 0));
    } // retranslateUi

};

namespace Ui {
    class test: public Ui_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEST_H
