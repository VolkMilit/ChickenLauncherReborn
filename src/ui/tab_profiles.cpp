#include "mainwindow.h"

void MainWindow::on_btn_profiles_new_clicked()
{
    newProfileDialog dialog;
    bool ok = dialog.exec();

    if (ok)
        TableHelper::addItem(ui->tw_profiles, ":/gzdoom.svg", dialog.getName(), dialog.getPort());

    dialog.done(0);
}

void MainWindow::populateProfilesTable()
{
    ui->tw_profiles->setIconSize(QSize(50, 25));

    const QStringList &scan = DirectoryList::scan(settings->getProfilesDir(), QStringList() << "*.ini");

    for (auto i = 0; i < scan.size(); ++i)
    {
        const QString &port = settings->readSettings(scan.at(i), "Port", "GamePort");
        QString profileRow = scan.at(i);

        QFileInfo profile(profileRow.remove(".ini"));

        if (port == "GZDoom")
            TableHelper::addItem(ui->tw_profiles, ":/gzdoom.svg", profile.baseName(), port);
        else if (port == "Darkplaces")
            TableHelper::addItem(ui->tw_profiles, ":/darkplaces.svg", profile.baseName(), port);
        else if (port == "UHexen2")
            TableHelper::addItem(ui->tw_profiles, ":/uhexen2.svg", profile.baseName(), port);
        else if (port == "dhewm3")
            TableHelper::addItem(ui->tw_profiles, ":/dhewm3.svg", profile.baseName(), port);
    }
}

void MainWindow::on_btn_profiles_rename_clicked()
{
    QTableWidgetItem *item = ui->tw_profiles->currentItem();
    QString profilesDir = settings->getProfilesDir();

    if (!item)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Rename profile '") + item->text() + "'",
                                             tr("New profile name:"), QLineEdit::Normal,
                                             item->text(), &ok);

    QFile file(profilesDir + text + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Profile already exist.", QMessageBox::Ok);
        return;
    }

    if (ok && !text.isEmpty())
    {
        if (settings->getDefaultProfileName() == item->text())
            settings->setCurrentProfile(text);

        QFile::rename(profilesDir + item->text() + ".ini", profilesDir + text + ".ini");
        item->setText(text);
    }
}

void MainWindow::on_btn_profiles_delete_clicked()
{
    QTableWidgetItem *item = ui->tw_profiles->currentItem();

    if (!item)
        return;

    QMessageBox message;
    message.setText("Warning!");
    message.setInformativeText("Are you sure you want to delete " + item->text() + " profile?");
    message.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    message.setDefaultButton(QMessageBox::Cancel);
    int ok = message.exec();

    if (ok == QMessageBox::Ok)
    {
        QFile file(settings->getProfilesDir() + item->text() + ".ini");
        file.remove();

        ui->tw_profiles->removeRow(item->row());

        ui->tw_profiles->setCurrentCell(0, 0);
        QTableWidgetItem *item = ui->tw_profiles->currentItem();
        settings->setCurrentProfile(item->text());
    }
}

void MainWindow::on_btn_profiles_clone_clicked()
{
    QTableWidgetItem *item = ui->tw_profiles->currentItem();

    if (!item)
        return;

    bool ok;
    QString text = QInputDialog::getText(this, tr("Copy profile '") + item->text() + "'",
                                             tr("New profile name:"), QLineEdit::Normal,
                                             item->text(), &ok);

    QFile file(settings->getProfilesDir() + text + ".ini");
    if (file.exists())
    {
        QMessageBox::warning(this, "Error", "Profile already exist.", QMessageBox::Ok);
        return;
    }

    if (ok && !text.isEmpty())
    {
        QString profilesDir = settings->getProfilesDir();

        QFile::copy(profilesDir + item->text() + ".ini", profilesDir + text + ".ini");

        TableHelper::addItem(ui->tw_profiles, ":/doom.png", text, ui->tw_profiles->item(item->row(), 1)->text());
        TableHelper::selectItem(ui->tw_profiles, text);
        QTableWidgetItem *item = ui->tw_profiles->currentItem();
        settings->setCurrentProfile(item->text());
    }
}

void MainWindow::on_btn_profiles_load_clicked()
{
    TableHelper::setStandartFont(ui->tw_profiles);

    writeSettings();

    QFont font;
    font.setBold(true);
    int row = ui->tw_profiles->currentRow();

    settings->setCurrentProfile(ui->tw_profiles->item(row, 1)->text());
    //ui->tw_profiles->item(row, 0)->setFont(font);
    ui->tw_profiles->item(row, 1)->setFont(font);

    checkedItems.clear();
    ui->lw_iwad->clear();
    ui->lw_pwad->clear();
    ui->le_iwaddir->clear();
    ui->le_pwaddir->clear();

    this->setWindowTitle("ChickenLauncher - " + ui->tw_profiles->item(ui->tw_profiles->currentRow(), 0)->text());

    readSettings();
}
