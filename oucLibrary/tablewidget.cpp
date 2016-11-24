#include "tablewidget.h"

TableWidget::TableWidget(QWidget *parent) : QWidget(parent), table(new QTableWidget(this)), page(new PageWidget(3, this))
{
}

TableWidget::TableWidget(TableWidget *tablewidget) : table(tablewidget->table), page(tablewidget->page)
{
}

void TableWidget::resizeEvent(QResizeEvent *event)
{
    table->setGeometry(0, 0, width(), height()-20);
    page->setGeometry(0, height()-20, width(), 20);

    QWidget::resizeEvent(event);
}

