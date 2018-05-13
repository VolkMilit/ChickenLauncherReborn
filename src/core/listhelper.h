#ifndef LISTHELPER_H
#define LISTHELPER_H

#include <QListWidget>
#include <QListWidgetItem>
#include <QFont>

class ListHelper
{
    public:
        static void addItem(QListWidget *widget, const QString &item);
        static void addItem(QListWidget *widget, const QString &item, Qt::CheckState checked);
        static QStringList getCheckedItems(QListWidget *widget);
        static void moveUp(QListWidget *widget);
        static void moveDown(QListWidget *widget);
        static void selectItem(QListWidget *widget, const QString &item);
        static void selectItem(QListWidget *widget, const QString &item, Qt::CheckState checked);

    private:
        ListHelper();
};

#endif // LISTHELPER_H
