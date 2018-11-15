#include "tablehelper.h"
#include <QDebug>

void TableHelper::addItem(QTableWidget *widget, const QString &icon, const QString &item1, const QString &item2)
{
    QTableWidgetItem *witem0 = new QTableWidgetItem(item1);
    QTableWidgetItem *witem1 = new QTableWidgetItem(item2);

    witem0->setIcon(QIcon(icon));

    int row;

    if (widget->rowCount() == 0)
        row = 0;
    else
        row = widget->rowCount()-1;

    widget->insertRow(row);

    widget->setItem(row, 0, witem0);
    widget->setItem(row, 1, witem1);
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
