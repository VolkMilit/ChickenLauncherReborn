#ifndef TABLEHELPER_H
#define TABLEHELPER_H

#include <QTableWidget>
#include <QTableWidgetItem>

class TableHelper
{
    public:
        static void addItem(QTableWidget *widget, const QString &item1, const QString &item2);
        static void selectItem(QTableWidget *widget, const QString &item);

    private:
        TableHelper();
};

#endif // TABLEHELPER_H
