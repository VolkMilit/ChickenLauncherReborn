#include "tablehelper.h"
#include <QDebug>

void TableHelper::addItem(QTableWidget *widget, const QString &item1, const QString &item2)
{
    QTableWidgetItem *witem1 = new QTableWidgetItem(item1);
    QTableWidgetItem *witem2 = new QTableWidgetItem(item2);

    int row;

    if (widget->rowCount() == 0)
        row = 0;
    else
        row = widget->rowCount()-1;

    widget->insertRow(row);

    widget->setItem(row, 0, witem1);
    widget->setItem(row, 1, witem2);
}

void TableHelper::selectItem(QTableWidget *widget, const QString &item)
{
    QFont font;
    font.setBold(true);

    for (auto i = 0; i < widget->rowCount(); i++)
    {
        if (widget->item(i, 0)->text() == item)
        {
            widget->selectRow(i);
            widget->item(i, 0)->setFont(font);
            widget->item(i, 1)->setFont(font);
        }
    }
}

void TableHelper::setStandartFont(QTableWidget *widget)
{
    QFont font;
    font.setBold(false);

    for (int i = 0; i < widget->rowCount(); i++)
    {
        widget->item(i, 0)->setFont(font);
        widget->item(i, 1)->setFont(font);
    }
}
