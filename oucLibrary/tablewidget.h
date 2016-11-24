#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include "pagewidget.h"

#include <QWidget>
#include <QTableWidget>

class TableWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TableWidget(QWidget *parent = 0);
    TableWidget(TableWidget * tablewidget);
    QTableWidget * table;
    PageWidget * page;

protected:
    void resizeEvent(QResizeEvent * event);
};

#endif // TABLEWIDGET_H
