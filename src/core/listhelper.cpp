#include "listhelper.h"
#include <QDebug>

void ListHelper::addItem(QListWidget *widget, const QString &item)
{
    widget->addItem(item);
}

void ListHelper::addItem(QListWidget *widget, const QString &item, Qt::CheckState checked)
{
    QListWidgetItem *witem = new QListWidgetItem(item);
    witem->setCheckState(checked);
    widget->addItem(witem);
}

QStringList ListHelper::getCheckedItems(QListWidget *widget)
{
    QStringList list;

    for (auto i = 0; i < widget->count(); i++)
    {
        if (widget->item(i)->checkState() == Qt::Checked)
        {
            list.append(widget->item(i)->text());
        }
    }

    return list;
}

void ListHelper::moveUp(QListWidget *widget)
{
    QListWidgetItem *current = widget->currentItem();

    if (current == nullptr)
        return;

    int currIndex = widget->row(current);

    QListWidgetItem *item = widget->item(currIndex - 1);

    int index = widget->row(item);

    QListWidgetItem *temp = widget->takeItem(index);

    widget->insertItem(index, current);
    widget->insertItem(currIndex, temp);
}

void ListHelper::moveDown(QListWidget *widget)
{
    QListWidgetItem *current = widget->currentItem();

    if (current == nullptr)
        return;

    int currIndex = widget->row(current);

    QListWidgetItem *item = widget->item(currIndex + 1);

    int index = widget->row(item);

    QListWidgetItem *temp = widget->takeItem(index);

    widget->insertItem(currIndex, temp);
    widget->insertItem(index, current);
}

void ListHelper::selectItem(QListWidget *widget, const QString &item)
{
    for (auto i = 0; i < widget->count(); i++)
    {
        QListWidgetItem *witem = widget->item(i);

        if (witem->text().contains(item))
        {
            witem->setSelected(true);
            widget->setCurrentItem(witem);
        }
    }
}

void ListHelper::selectItem(QListWidget *widget, const QString &item, Qt::CheckState checked)
{
    for (auto i = 0; i < widget->count(); i++)
    {
        QListWidgetItem *witem = widget->item(i);

        if (witem->text() == item)
            witem->setCheckState(checked);
    }
}
