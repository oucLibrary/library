#ifndef CHANGEPERSON_H
#define CHANGEPERSON_H

#include <QWidget>

namespace Ui {
class changePerson;
}

class changePerson : public QWidget
{
    Q_OBJECT

public:
    explicit changePerson(QWidget *parent = 0);
    ~changePerson();

private:
    Ui::changePerson *ui;
};

#endif // CHANGEPERSON_H
