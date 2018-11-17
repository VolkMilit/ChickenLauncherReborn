#include "mainwindow.h"

void MainWindow::populateIwadList()
{
    ui->lw_iwad->clear();
    ui->lw_iwad->setIconSize(QSize(50, 25));

    const QStringList &scan = DirectoryList::scan(ui->le_iwaddir->text(), QStringList() << "*.wad" << "*.pk3" << "*.zip");

    for (const QString &item : scan)
    {
        QFileInfo fi(item);

        if (!fi.baseName().compare("doom2", Qt::CaseInsensitive))
            ListHelper::addItem(ui->lw_iwad, item, ":/doom2.png");
        else if (!fi.baseName().compare("doom", Qt::CaseInsensitive))
            ListHelper::addItem(ui->lw_iwad, item, ":/doom.png");
    }
}

void MainWindow::populatePwadList()
{
    ui->lw_pwad->clear();

    const QStringList &scan = DirectoryList::scan(ui->le_pwaddir->text(), QStringList() << "*.wad" << "*.pk3" << "*.zip");

    for (const QString &item : scan)
        ListHelper::addItem(ui->lw_pwad, item, Qt::Unchecked);
}

void MainWindow::on_lw_iwad_itemActivated(QListWidgetItem *item)
{
    settings->setLastIwad(item->text());
}

void MainWindow::on_lw_pwad_itemChanged()
{
    checkedItems = ListHelper::getCheckedItems(ui->lw_pwad);
}

void MainWindow::on_btn_pwad_up_clicked()
{
    ListHelper::moveUp(ui->lw_pwad);
}

void MainWindow::on_btn_pwad_down_clicked()
{
    ListHelper::moveDown(ui->lw_pwad);
}

void MainWindow::on_btn_refresh_clicked()
{
    populatePwadList();

    foreach (const QString &item, checkedItems) // DO NOT use std foreach here, it will segfault
       ListHelper::selectItem(ui->lw_pwad, item, Qt::Checked);
}

void MainWindow::on_lw_pwad_itemChanged(QListWidgetItem *item)
{
    QFont font;

    if (item->checkState() == Qt::Checked)
        font.setBold(true);
    else
        font.setBold(false);

    item->setFont(font);
}

void MainWindow::on_lw_iwad_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    if (previous != nullptr)
    {
        QFont font2;
        font2.setBold(false);

        previous->setFont(font2);
    }

    if (current != nullptr)
    {
        QFont font;
        font.setBold(true);

        current->setFont(font);

        ui->btn_ripandtear->setIcon(current->icon());
        QFileInfo fi(current->text());
        ui->btn_ripandtear->setText("Play " + fi.completeBaseName());
    }
}
